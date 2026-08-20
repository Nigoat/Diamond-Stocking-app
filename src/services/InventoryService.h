#ifndef INVENTORYSERVICE_H
#define INVENTORYSERVICE_H

#include "Diamond.h"
#include "DiamondRepository.h"
#include <QList>
#include <optional>

class InventoryService {
public:
    static InventoryService &instance();

    bool addDiamond(Diamond &diamond, QString *errorMessage = nullptr);
    bool updateDiamond(const Diamond &diamond, QString *errorMessage = nullptr);
    bool archiveDiamond(qint64 id, QString *errorMessage = nullptr);
    bool restoreDiamond(qint64 id, QString *errorMessage = nullptr);
    bool toggleFavorite(qint64 id, QString *errorMessage = nullptr);
    bool deletePermanently(qint64 id, QString *errorMessage = nullptr);
    std::optional<Diamond> duplicateDiamond(qint64 id, QString *errorMessage = nullptr);

    bool bulkUpdateStatus(const QList<qint64> &ids, const QString &status, QString *errorMessage = nullptr);
    bool bulkAdjustPrice(const QList<qint64> &ids, double percent, QString *errorMessage = nullptr);
    bool bulkArchive(const QList<qint64> &ids, bool archive, QString *errorMessage = nullptr);

    QString generateNextReference(const QString &prefix = QStringLiteral("DMD-"));

private:
    InventoryService() = default;
    ~InventoryService() = default;
    InventoryService(const InventoryService &) = delete;
    InventoryService &operator=(const InventoryService &) = delete;
};

#endif
