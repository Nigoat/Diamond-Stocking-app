#include "ImageService.h"
#include "AppPaths.h"
#include "FileUtils.h"
#include "DiamondRepository.h"
#include "AuditRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QImage>
#include <QFileInfo>
#include <QUuid>
#include <QUrl>

ImageService &ImageService::instance() {
    static ImageService inst;
    return inst;
}

std::optional<DiamondImage> ImageService::saveImageForDiamond(qint64 diamondId, const QString &sourcePath,
                                                             const QString &imageType, QString *errorMessage) {
    QString cleanSource = sourcePath;
    if (cleanSource.startsWith(QStringLiteral("file://"))) {
        cleanSource = QUrl(sourcePath).toLocalFile();
    }

    QFileInfo srcInfo(cleanSource);
    if (!srcInfo.exists() || !srcInfo.isFile()) {
        if (errorMessage) *errorMessage = QStringLiteral("Source image file does not exist: %1").arg(cleanSource);
        return std::nullopt;
    }

    QImage img;
    if (!img.load(cleanSource)) {
        if (errorMessage) *errorMessage = QStringLiteral("Failed to read image file format: %1").arg(cleanSource);
        return std::nullopt;
    }

    QString ext = srcInfo.suffix().toLower();
    if (ext.isEmpty()) ext = QStringLiteral("jpg");

    QString uniqueId = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString baseFilename = QStringLiteral("img_%1.%2").arg(uniqueId, ext);
    QString thumbFilename = QStringLiteral("thumb_%1.jpg").arg(uniqueId);

    QString targetDir = AppPaths::instance().diamondImagesDir(diamondId);
    QString thumbDir = AppPaths::instance().diamondThumbnailsDir(diamondId);

    QString fullImagePath = targetDir + QStringLiteral("/") + baseFilename;
    QString fullThumbPath = thumbDir + QStringLiteral("/") + thumbFilename;

    if (!img.save(fullImagePath)) {
        if (!FileUtils::copyFile(cleanSource, fullImagePath)) {
            if (errorMessage) *errorMessage = QStringLiteral("Failed to save image to application storage.");
            return std::nullopt;
        }
    }

    QImage thumb = img.scaled(256, 256, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    int cropX = std::max(0, (thumb.width() - 256) / 2);
    int cropY = std::max(0, (thumb.height() - 256) / 2);
    thumb = thumb.copy(cropX, cropY, 256, 256);
    if (!thumb.save(fullThumbPath, "JPG", 85)) {
        img.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation).save(fullThumbPath, "JPG", 80);
    }

    DiamondRepository repo;
    QList<DiamondImage> existing = repo.getImages(diamondId);
    QString finalType = imageType;
    if (existing.isEmpty()) {
        finalType = QStringLiteral("main");
    }

    DiamondImage diamondImg;
    diamondImg.setDiamondId(diamondId);
    diamondImg.setFilePath(fullImagePath);
    diamondImg.setThumbnailPath(fullThumbPath);
    diamondImg.setImageType(finalType);
    diamondImg.setSortOrder(static_cast<int>(existing.size()));

    if (!repo.insertImage(diamondImg, errorMessage)) {
        FileUtils::removeFile(fullImagePath);
        FileUtils::removeFile(fullThumbPath);
        return std::nullopt;
    }

    AuditRepository audit;
    audit.logAction(diamondId, QStringLiteral("Image Added"), QStringLiteral("image"), QString(), baseFilename);

    return diamondImg;
}

bool ImageService::removeImage(qint64 imageId, QString *errorMessage) {
    DiamondRepository repo;
    DiamondImage targetImg;
    bool found = false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("SELECT id, diamond_id, file_path, thumbnail_path, image_type, sort_order FROM diamond_images WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), imageId);
    if (q.exec() && q.next()) {
        targetImg.setId(q.value(0).toLongLong());
        targetImg.setDiamondId(q.value(1).toLongLong());
        targetImg.setFilePath(q.value(2).toString());
        targetImg.setThumbnailPath(q.value(3).toString());
        targetImg.setImageType(q.value(4).toString());
        targetImg.setSortOrder(q.value(5).toInt());
        found = true;
    }

    if (!found) {
        if (errorMessage) *errorMessage = QStringLiteral("Image record not found.");
        return false;
    }

    FileUtils::removeFile(targetImg.filePath());
    FileUtils::removeFile(targetImg.thumbnailPath());

    if (!repo.deleteImage(imageId, errorMessage)) {
        return false;
    }

    if (targetImg.imageType() == QStringLiteral("main")) {
        QList<DiamondImage> remaining = repo.getImages(targetImg.diamondId());
        if (!remaining.isEmpty()) {
            repo.setMainImage(targetImg.diamondId(), remaining.first().id());
        }
    }

    AuditRepository audit;
    audit.logAction(targetImg.diamondId(), QStringLiteral("Image Removed"), QStringLiteral("image"), QFileInfo(targetImg.filePath()).fileName(), QString());

    return true;
}

bool ImageService::setMainImage(qint64 diamondId, qint64 imageId, QString *errorMessage) {
    DiamondRepository repo;
    return repo.setMainImage(diamondId, imageId, errorMessage);
}

QList<DiamondImage> ImageService::getDiamondImages(qint64 diamondId) {
    DiamondRepository repo;
    return repo.getImages(diamondId);
}
