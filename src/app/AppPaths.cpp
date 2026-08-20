#include "AppPaths.h"
#include "FileUtils.h"
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

AppPaths::AppPaths() {
    QString base = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (base.isEmpty()) {
        base = QDir::homePath() + QStringLiteral("/.diamond_inventory");
    }
    m_appDataDir = base;
}

AppPaths &AppPaths::instance() {
    static AppPaths inst;
    return inst;
}

void AppPaths::initialize() {
    FileUtils::ensureDirExists(m_appDataDir);
    FileUtils::ensureDirExists(databaseDir());
    FileUtils::ensureDirExists(imagesDir());
    FileUtils::ensureDirExists(thumbnailsDir());
    FileUtils::ensureDirExists(backupsDir());
    FileUtils::ensureDirExists(logsDir());
    FileUtils::ensureDirExists(exportsDir());
}

QString AppPaths::appDataDir() const {
    return m_appDataDir;
}

QString AppPaths::databaseDir() const {
    return m_appDataDir + QStringLiteral("/database");
}

QString AppPaths::databaseFilePath() const {
    return databaseDir() + QStringLiteral("/inventory.db");
}

QString AppPaths::imagesDir() const {
    return m_appDataDir + QStringLiteral("/images");
}

QString AppPaths::thumbnailsDir() const {
    return m_appDataDir + QStringLiteral("/thumbnails");
}

QString AppPaths::backupsDir() const {
    return m_appDataDir + QStringLiteral("/backups");
}

QString AppPaths::logsDir() const {
    return m_appDataDir + QStringLiteral("/logs");
}

QString AppPaths::exportsDir() const {
    return m_appDataDir + QStringLiteral("/exports");
}

QString AppPaths::diamondImagesDir(qint64 diamondId) const {
    QString path = imagesDir() + QStringLiteral("/diamonds/%1").arg(diamondId);
    FileUtils::ensureDirExists(path);
    return path;
}

QString AppPaths::diamondThumbnailsDir(qint64 diamondId) const {
    QString path = thumbnailsDir() + QStringLiteral("/diamonds/%1").arg(diamondId);
    FileUtils::ensureDirExists(path);
    return path;
}
