#ifndef IMPORTSERVICE_H
#define IMPORTSERVICE_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QVariantMap>

struct ImportPreviewResult {
    bool success = false;
    QString errorMessage;
    QStringList headers;
    QList<QStringList> previewRows;
    int totalRows = 0;

    QVariantMap toVariantMap() const;
};

struct ImportExecutionResult {
    bool success = false;
    int totalRows = 0;
    int importedCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    QStringList errors;
    QStringList warnings;

    QVariantMap toVariantMap() const;
};

class ImportService {
public:
    static ImportService &instance();

    ImportPreviewResult previewCsv(const QString &filePath);
    ImportExecutionResult executeImport(const QString &filePath, const QVariantMap &columnMap);

private:
    ImportService() = default;
    ~ImportService() = default;
    ImportService(const ImportService &) = delete;
    ImportService &operator=(const ImportService &) = delete;

    QList<QStringList> parseCsvFile(const QString &filePath, QString *errorMessage);
};

#endif
