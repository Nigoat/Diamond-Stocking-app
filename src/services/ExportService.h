#ifndef EXPORTSERVICE_H
#define EXPORTSERVICE_H

#include "DiamondRepository.h"
#include <QString>

class ExportService {
public:
    static ExportService &instance();

    bool exportToCsv(const QString &filePath, const DiamondFilterCriteria &criteria, QString *errorMessage = nullptr);
    bool exportToPdf(const QString &filePath, const DiamondFilterCriteria &criteria, QString *errorMessage = nullptr);

private:
    ExportService() = default;
    ~ExportService() = default;
    ExportService(const ExportService &) = delete;
    ExportService &operator=(const ExportService &) = delete;
};

#endif
