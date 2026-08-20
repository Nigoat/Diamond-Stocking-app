#include "ReportService.h"
#include "DatabaseManager.h"
#include "DiamondRepository.h"
#include "Money.h"
#include <QSqlQuery>
#include <QSqlError>

QVariantMap DashboardStats::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("totalCount")] = totalCount;
    map[QStringLiteral("availableCount")] = availableCount;
    map[QStringLiteral("reservedCount")] = reservedCount;
    map[QStringLiteral("soldCount")] = soldCount;
    map[QStringLiteral("otherStatusCount")] = otherStatusCount;
    map[QStringLiteral("totalPurchaseCostCents")] = totalPurchaseCostCents;
    map[QStringLiteral("totalSellingValueCents")] = totalSellingValueCents;
    map[QStringLiteral("potentialMarginCents")] = potentialMarginCents;
    map[QStringLiteral("potentialMarginPercentage")] = potentialMarginPercentage;
    map[QStringLiteral("totalPurchaseCostFormatted")] = Money::fromCents(totalPurchaseCostCents).formatted();
    map[QStringLiteral("totalSellingValueFormatted")] = Money::fromCents(totalSellingValueCents).formatted();
    map[QStringLiteral("potentialMarginFormatted")] = Money::fromCents(potentialMarginCents).formatted();
    map[QStringLiteral("missingImagesCount")] = missingImagesCount;
    map[QStringLiteral("missingCertificatesCount")] = missingCertificatesCount;
    map[QStringLiteral("recentlyAdded")] = recentlyAdded;
    map[QStringLiteral("recentlyUpdated")] = recentlyUpdated;
    return map;
}

ReportService &ReportService::instance() {
    static ReportService inst;
    return inst;
}

DashboardStats ReportService::getDashboardStats() {
    DashboardStats stats;
    if (!DatabaseManager::instance().isOpen()) return stats;

    QSqlDatabase db = DatabaseManager::instance().database();

    QSqlQuery qTotals(QStringLiteral(
        "SELECT "
        "COUNT(*), "
        "COALESCE(SUM(CASE WHEN status = 'Available' THEN 1 ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN status = 'Reserved' THEN 1 ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN status = 'Sold' THEN 1 ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN status = 'Available' THEN purchase_price_cents ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN status = 'Available' THEN selling_price_cents ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN (certificate_number IS NULL OR length(trim(certificate_number)) = 0) THEN 1 ELSE 0 END), 0), "
        "COALESCE(SUM(CASE WHEN (SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = diamonds.id) = 0 THEN 1 ELSE 0 END), 0) "
        "FROM diamonds WHERE archived = 0"
    ), db);

    if (qTotals.exec() && qTotals.next()) {
        stats.totalCount = qTotals.value(0).toLongLong();
        stats.availableCount = qTotals.value(1).toLongLong();
        stats.reservedCount = qTotals.value(2).toLongLong();
        stats.soldCount = qTotals.value(3).toLongLong();
        stats.otherStatusCount = stats.totalCount - (stats.availableCount + stats.reservedCount + stats.soldCount);
        stats.totalPurchaseCostCents = qTotals.value(4).toLongLong();
        stats.totalSellingValueCents = qTotals.value(5).toLongLong();
        stats.potentialMarginCents = stats.totalSellingValueCents - stats.totalPurchaseCostCents;
        stats.potentialMarginPercentage = Money::calculateMarginPercentage(
            Money::fromCents(stats.totalSellingValueCents),
            Money::fromCents(stats.totalPurchaseCostCents)
        );
        stats.missingCertificatesCount = qTotals.value(6).toLongLong();
        stats.missingImagesCount = qTotals.value(7).toLongLong();
    }

    DiamondRepository repo;
    DiamondFilterCriteria criteriaAdded;
    criteriaAdded.sortBy = QStringLiteral("created_at");
    criteriaAdded.sortAscending = false;
    criteriaAdded.includeArchived = false;
    QList<Diamond> recentAdded = repo.getList(criteriaAdded);
    for (int i = 0; i < std::min(static_cast<int>(recentAdded.size()), 5); ++i) {
        stats.recentlyAdded.append(recentAdded[i].toVariantMap());
    }

    DiamondFilterCriteria criteriaUpdated;
    criteriaUpdated.sortBy = QStringLiteral("updated_at");
    criteriaUpdated.sortAscending = false;
    criteriaUpdated.includeArchived = false;
    QList<Diamond> recentUpdated = repo.getList(criteriaUpdated);
    for (int i = 0; i < std::min(static_cast<int>(recentUpdated.size()), 5); ++i) {
        stats.recentlyUpdated.append(recentUpdated[i].toVariantMap());
    }

    return stats;
}

QVariantMap ReportService::getReportsBreakdown() {
    QVariantMap res;
    if (!DatabaseManager::instance().isOpen()) return res;

    QSqlDatabase db = DatabaseManager::instance().database();

    auto runAggregation = [&](const QString &sql) -> QVariantList {
        QVariantList list;
        QSqlQuery q(sql, db);
        if (q.exec()) {
            while (q.next()) {
                QVariantMap item;
                item[QStringLiteral("label")] = q.value(0).toString();
                item[QStringLiteral("count")] = q.value(1).toLongLong();
                item[QStringLiteral("totalValueCents")] = q.value(2).toLongLong();
                item[QStringLiteral("totalValueFormatted")] = Money::fromCents(q.value(2).toLongLong()).formatted();
                list.append(item);
            }
        }
        return list;
    };

    res[QStringLiteral("byShape")] = runAggregation(
        QStringLiteral("SELECT shape, COUNT(*), COALESCE(SUM(selling_price_cents), 0) FROM diamonds WHERE archived = 0 GROUP BY shape ORDER BY COUNT(*) DESC")
    );
    res[QStringLiteral("byColor")] = runAggregation(
        QStringLiteral("SELECT color, COUNT(*), COALESCE(SUM(selling_price_cents), 0) FROM diamonds WHERE archived = 0 GROUP BY color ORDER BY color ASC")
    );
    res[QStringLiteral("byClarity")] = runAggregation(
        QStringLiteral("SELECT clarity, COUNT(*), COALESCE(SUM(selling_price_cents), 0) FROM diamonds WHERE archived = 0 GROUP BY clarity ORDER BY COUNT(*) DESC")
    );
    res[QStringLiteral("byStatus")] = runAggregation(
        QStringLiteral("SELECT status, COUNT(*), COALESCE(SUM(selling_price_cents), 0) FROM diamonds WHERE archived = 0 GROUP BY status ORDER BY COUNT(*) DESC")
    );
    res[QStringLiteral("bySupplier")] = runAggregation(
        QStringLiteral("SELECT COALESCE(s.name, 'No Supplier'), COUNT(d.id), COALESCE(SUM(d.selling_price_cents), 0) FROM diamonds d LEFT JOIN suppliers s ON s.id = d.supplier_id WHERE d.archived = 0 GROUP BY s.id ORDER BY COUNT(d.id) DESC")
    );

    return res;
}
