#include "BackupService.h"
#include "AppPaths.h"
#include "FileUtils.h"
#include "DateUtils.h"
#include "AppSettings.h"
#include "DatabaseManager.h"
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

QVariantMap BackupInfo::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("fileName")] = fileName;
    map[QStringLiteral("fullPath")] = fullPath;
    map[QStringLiteral("dateFormatted")] = dateFormatted;
    map[QStringLiteral("sizeFormatted")] = sizeFormatted;
    map[QStringLiteral("sizeBytes")] = sizeBytes;
    map[QStringLiteral("diamondCount")] = diamondCount;
    return map;
}

BackupService &BackupService::instance() {
    static BackupService inst;
    return inst;
}

bool BackupService::createBackup(QString *createdPath, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) {
        if (errorMessage) *errorMessage = QStringLiteral("Database is not open.");
        return false;
    }

    QString ts = DateUtils::formatTimestampForFilename();
    QString fileName = QStringLiteral("inventory_%1.db").arg(ts);
    QString backupDir = AppPaths::instance().backupsDir();
    FileUtils::ensureDirExists(backupDir);
    QString dstPath = backupDir + QStringLiteral("/") + fileName;

    QSqlQuery walCheckpoint(QStringLiteral("PRAGMA wal_checkpoint(TRUNCATE);"), DatabaseManager::instance().database());
    walCheckpoint.exec();

    QSqlQuery vacuum(QStringLiteral("VACUUM INTO '%1'").arg(dstPath), DatabaseManager::instance().database());
    if (!vacuum.exec()) {
        QString srcPath = AppPaths::instance().databaseFilePath();
        if (!FileUtils::copyFile(srcPath, dstPath)) {
            if (errorMessage) *errorMessage = QStringLiteral("Failed to copy database for backup: %1").arg(vacuum.lastError().text());
            return false;
        }
    }

    AppSettings::instance().setLastBackupDate(QDateTime::currentDateTimeUtc().toString(Qt::ISODate));
    cleanOldBackups(15);

    if (createdPath) *createdPath = dstPath;
    return true;
}

bool BackupService::restoreBackup(const QString &backupPath, QString *errorMessage) {
    QFileInfo bInfo(backupPath);
    if (!bInfo.exists() || !bInfo.isFile()) {
        if (errorMessage) *errorMessage = QStringLiteral("Backup file does not exist: %1").arg(backupPath);
        return false;
    }

    {
        QString testConn = QStringLiteral("RestoreVerifyConn");
        {
            QSqlDatabase testDb = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), testConn);
            testDb.setDatabaseName(backupPath);
            if (!testDb.open()) {
                if (errorMessage) *errorMessage = QStringLiteral("Backup file is corrupt or invalid SQLite database.");
                return false;
            }
            QSqlQuery testQ(testDb);
            if (!testQ.exec(QStringLiteral("SELECT COUNT(*) FROM diamonds"))) {
                if (errorMessage) *errorMessage = QStringLiteral("Backup file is missing required diamonds table.");
                testDb.close();
                return false;
            }
            testDb.close();
        }
        QSqlDatabase::removeDatabase(testConn);
    }

    QString safetyPath;
    createBackup(&safetyPath);

    DatabaseManager::instance().close();

    QString currentDbPath = AppPaths::instance().databaseFilePath();
    FileUtils::removeFile(currentDbPath + QStringLiteral("-wal"));
    FileUtils::removeFile(currentDbPath + QStringLiteral("-shm"));

    if (!FileUtils::copyFile(backupPath, currentDbPath)) {
        if (errorMessage) *errorMessage = QStringLiteral("Failed to replace active database file with backup.");
        DatabaseManager::instance().initialize();
        return false;
    }

    if (!DatabaseManager::instance().initialize(currentDbPath)) {
        if (errorMessage) *errorMessage = DatabaseManager::instance().lastError();
        return false;
    }

    return true;
}

QList<BackupInfo> BackupService::listBackups() {
    QList<BackupInfo> list;
    QDir dir(AppPaths::instance().backupsDir());
    QFileInfoList entries = dir.entryInfoList({QStringLiteral("*.db")}, QDir::Files, QDir::Time);

    for (const QFileInfo &fi : entries) {
        BackupInfo info;
        info.fileName = fi.fileName();
        info.fullPath = fi.absoluteFilePath();
        info.sizeBytes = fi.size();
        info.sizeFormatted = FileUtils::formatFileSize(fi.size());
        info.dateFormatted = fi.lastModified().toString(QStringLiteral("dd/MM/yyyy HH:mm:ss"));

        QString tempConn = QStringLiteral("BackupCount_%1").arg(fi.fileName());
        {
            QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), tempConn);
            db.setDatabaseName(fi.absoluteFilePath());
            if (db.open()) {
                QSqlQuery q(QStringLiteral("SELECT COUNT(*) FROM diamonds WHERE archived = 0"), db);
                if (q.exec() && q.next()) {
                    info.diamondCount = q.value(0).toLongLong();
                }
                db.close();
            }
        }
        QSqlDatabase::removeDatabase(tempConn);

        list.append(info);
    }
    return list;
}

void BackupService::cleanOldBackups(int keepCount) {
    QDir dir(AppPaths::instance().backupsDir());
    QFileInfoList entries = dir.entryInfoList({QStringLiteral("*.db")}, QDir::Files, QDir::Time);
    if (entries.size() > keepCount) {
        for (int i = keepCount; i < entries.size(); ++i) {
            FileUtils::removeFile(entries[i].absoluteFilePath());
        }
    }
}

bool BackupService::checkAndPerformAutoBackup() {
    QString interval = AppSettings::instance().autoBackupInterval();
    if (interval == QStringLiteral("disabled")) return false;

    if (interval == QStringLiteral("always_on_close")) {
        return createBackup();
    }

    QString lastDateStr = AppSettings::instance().lastBackupDate();
    if (lastDateStr.isEmpty()) {
        return createBackup();
    }

    QDateTime lastDt = QDateTime::fromString(lastDateStr, Qt::ISODate);
    if (!lastDt.isValid()) {
        return createBackup();
    }

    qint64 secs = lastDt.secsTo(QDateTime::currentDateTimeUtc());
    if (interval == QStringLiteral("daily") && secs >= 86400) {
        return createBackup();
    }
    if (interval == QStringLiteral("weekly") && secs >= (7 * 86400)) {
        return createBackup();
    }
    return false;
}
