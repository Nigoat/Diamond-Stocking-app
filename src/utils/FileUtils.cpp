#include "FileUtils.h"
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>

bool FileUtils::ensureDirExists(const QString &dirPath) {
    QDir dir(dirPath);
    if (dir.exists()) return true;
    return dir.mkpath(QStringLiteral("."));
}

bool FileUtils::copyFile(const QString &srcPath, const QString &dstPath) {
    QFileInfo dstInfo(dstPath);
    if (!ensureDirExists(dstInfo.dir().absolutePath())) {
        return false;
    }
    if (QFile::exists(dstPath)) {
        QFile::remove(dstPath);
    }
    return QFile::copy(srcPath, dstPath);
}

bool FileUtils::removeFile(const QString &filePath) {
    if (filePath.isEmpty() || !QFile::exists(filePath)) return true;
    return QFile::remove(filePath);
}

QString FileUtils::sanitizeFilename(const QString &filename) {
    QString clean = filename;
    clean.replace(QRegularExpression(QStringLiteral("[^a-zA-Z0-9._-]")), QStringLiteral("_"));
    return clean;
}

QString FileUtils::formatFileSize(qint64 bytes) {
    if (bytes < 1024) {
        return QStringLiteral("%1 B").arg(bytes);
    } else if (bytes < 1024 * 1024) {
        return QStringLiteral("%1 KB").arg(QString::number(static_cast<double>(bytes) / 1024.0, 'f', 1));
    } else {
        return QStringLiteral("%1 MB").arg(QString::number(static_cast<double>(bytes) / (1024.0 * 1024.0), 'f', 2));
    }
}

QString FileUtils::fileExtension(const QString &filePath) {
    QFileInfo info(filePath);
    return info.suffix().toLower();
}
