#ifndef BACKUPSERVICE_H
#define BACKUPSERVICE_H

#include <QString>
#include <QList>
#include <QVariantMap>

struct BackupInfo {
    QString fileName;
    QString fullPath;
    QString dateFormatted;
    QString sizeFormatted;
    qint64 sizeBytes = 0;
    qint64 diamondCount = 0;

    QVariantMap toVariantMap() const;
};

class BackupService {
public:
    static BackupService &instance();

    bool createBackup(QString *createdPath = nullptr, QString *errorMessage = nullptr);
    bool restoreBackup(const QString &backupPath, QString *errorMessage = nullptr);
    QList<BackupInfo> listBackups();
    void cleanOldBackups(int keepCount = 10);
    bool checkAndPerformAutoBackup();

private:
    BackupService() = default;
    ~BackupService() = default;
    BackupService(const BackupService &) = delete;
    BackupService &operator=(const BackupService &) = delete;
};

#endif
