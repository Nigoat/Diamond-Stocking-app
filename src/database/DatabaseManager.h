#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QMutex>

class DatabaseManager {
public:
    static DatabaseManager &instance();

    bool initialize(const QString &dbPath = QString());
    void close();
    bool isOpen() const;

    QSqlDatabase database() const;
    QString lastError() const;

    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    bool seedDemoData();

private:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager &operator=(const DatabaseManager &) = delete;

    QString m_connectionName;
    QString m_dbPath;
    QString m_lastError;
    mutable QMutex m_mutex;
};

#endif
