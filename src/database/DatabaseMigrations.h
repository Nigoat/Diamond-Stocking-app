#ifndef DATABASEMIGRATIONS_H
#define DATABASEMIGRATIONS_H

#include <QSqlDatabase>
#include <QString>

class DatabaseMigrations {
public:
    static bool runMigrations(QSqlDatabase &db, QString *errorMessage = nullptr);

private:
    static int currentVersion(QSqlDatabase &db);
    static bool executeMigrationScript(QSqlDatabase &db, int version, const QString &sql, QString *errorMessage);
    static QString getMigrationSql(int version);
};

#endif
