#ifndef REPORTSERVICE_H
#define REPORTSERVICE_H

#include <QVariantMap>
#include <QVariantList>

struct DashboardStats {
    qint64 totalCount = 0;
    qint64 availableCount = 0;
    qint64 reservedCount = 0;
    qint64 soldCount = 0;
    qint64 otherStatusCount = 0;

    qint64 totalPurchaseCostCents = 0;
    qint64 totalSellingValueCents = 0;
    qint64 potentialMarginCents = 0;
    double potentialMarginPercentage = 0.0;

    qint64 missingImagesCount = 0;
    qint64 missingCertificatesCount = 0;

    QVariantList recentlyAdded;
    QVariantList recentlyUpdated;

    QVariantMap toVariantMap() const;
};

class ReportService {
public:
    static ReportService &instance();

    DashboardStats getDashboardStats();
    QVariantMap getReportsBreakdown();

private:
    ReportService() = default;
    ~ReportService() = default;
    ReportService(const ReportService &) = delete;
    ReportService &operator=(const ReportService &) = delete;
};

#endif
