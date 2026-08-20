#include "InventoryService.h"
#include "AuditRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QRandomGenerator>

InventoryService &InventoryService::instance() {
    static InventoryService inst;
    return inst;
}

bool InventoryService::addDiamond(Diamond &diamond, QString *errorMessage) {
    if (diamond.reference().trimmed().isEmpty()) {
        if (errorMessage) *errorMessage = QStringLiteral("Reference is required.");
        return false;
    }
    if (diamond.name().trimmed().isEmpty()) {
        if (errorMessage) *errorMessage = QStringLiteral("Name is required.");
        return false;
    }
    if (diamond.caratWeight() < 0.0) {
        if (errorMessage) *errorMessage = QStringLiteral("Carat weight cannot be negative.");
        return false;
    }
    if (diamond.purchasePriceCents() < 0 || diamond.sellingPriceCents() < 0) {
        if (errorMessage) *errorMessage = QStringLiteral("Price cannot be negative.");
        return false;
    }

    DiamondRepository repo;
    if (!repo.insert(diamond, errorMessage)) {
        return false;
    }

    AuditRepository audit;
    audit.logAction(diamond.id(), QStringLiteral("Diamond Created"), QStringLiteral("reference"), QString(), diamond.reference());
    return true;
}

bool InventoryService::updateDiamond(const Diamond &diamond, QString *errorMessage) {
    if (diamond.reference().trimmed().isEmpty()) {
        if (errorMessage) *errorMessage = QStringLiteral("Reference is required.");
        return false;
    }
    if (diamond.name().trimmed().isEmpty()) {
        if (errorMessage) *errorMessage = QStringLiteral("Name is required.");
        return false;
    }
    if (diamond.caratWeight() < 0.0) {
        if (errorMessage) *errorMessage = QStringLiteral("Carat weight cannot be negative.");
        return false;
    }
    if (diamond.purchasePriceCents() < 0 || diamond.sellingPriceCents() < 0) {
        if (errorMessage) *errorMessage = QStringLiteral("Price cannot be negative.");
        return false;
    }

    DiamondRepository repo;
    auto existing = repo.getById(diamond.id());
    if (!existing.has_value()) {
        if (errorMessage) *errorMessage = QStringLiteral("Diamond not found.");
        return false;
    }

    if (!repo.update(diamond, errorMessage)) {
        return false;
    }

    AuditRepository audit;
    Diamond oldD = existing.value();
    if (oldD.sellingPriceCents() != diamond.sellingPriceCents()) {
        audit.logAction(diamond.id(), QStringLiteral("Price Changed"), QStringLiteral("selling_price"),
                        oldD.sellingPrice().formatted(), diamond.sellingPrice().formatted());
    }
    if (oldD.status() != diamond.status()) {
        audit.logAction(diamond.id(), QStringLiteral("Status Changed"), QStringLiteral("status"),
                        oldD.status(), diamond.status());
    }
    if (oldD.location() != diamond.location() || oldD.locationDetails() != diamond.locationDetails()) {
        audit.logAction(diamond.id(), QStringLiteral("Location Changed"), QStringLiteral("location"),
                        oldD.location(), diamond.location());
    }
    if (oldD.certificateNumber() != diamond.certificateNumber()) {
        audit.logAction(diamond.id(), QStringLiteral("Certificate Updated"), QStringLiteral("certificate_number"),
                        oldD.certificateNumber(), diamond.certificateNumber());
    }

    return true;
}

bool InventoryService::archiveDiamond(qint64 id, QString *errorMessage) {
    DiamondRepository repo;
    if (!repo.setArchived(id, true, errorMessage)) {
        return false;
    }
    AuditRepository audit;
    audit.logAction(id, QStringLiteral("Archived"), QStringLiteral("archived"), QStringLiteral("0"), QStringLiteral("1"));
    return true;
}

bool InventoryService::restoreDiamond(qint64 id, QString *errorMessage) {
    DiamondRepository repo;
    if (!repo.setArchived(id, false, errorMessage)) {
        return false;
    }
    AuditRepository audit;
    audit.logAction(id, QStringLiteral("Restored"), QStringLiteral("archived"), QStringLiteral("1"), QStringLiteral("0"));
    return true;
}

bool InventoryService::toggleFavorite(qint64 id, QString *errorMessage) {
    DiamondRepository repo;
    auto opt = repo.getById(id);
    if (!opt.has_value()) {
        if (errorMessage) *errorMessage = QStringLiteral("Diamond not found.");
        return false;
    }
    bool newFav = !opt.value().isFavorite();
    return repo.setFavorite(id, newFav, errorMessage);
}

bool InventoryService::deletePermanently(qint64 id, QString *errorMessage) {
    DiamondRepository repo;
    return repo.deletePermanently(id, errorMessage);
}

std::optional<Diamond> InventoryService::duplicateDiamond(qint64 id, QString *errorMessage) {
    DiamondRepository repo;
    auto opt = repo.getById(id);
    if (!opt.has_value()) {
        if (errorMessage) *errorMessage = QStringLiteral("Source diamond not found.");
        return std::nullopt;
    }

    Diamond src = opt.value();
    Diamond copy = src;
    copy.setId(0);
    copy.setReference(generateNextReference());
    copy.setName(src.name() + QStringLiteral(" (Copy)"));
    copy.setCertificateNumber(QString());
    copy.setStatus(QStringLiteral("Available"));
    copy.setIsFavorite(false);
    copy.setArchived(false);

    if (!repo.insert(copy, errorMessage)) {
        return std::nullopt;
    }

    AuditRepository audit;
    audit.logAction(copy.id(), QStringLiteral("Duplicated from %1").arg(src.reference()), QStringLiteral("reference"), src.reference(), copy.reference());

    return copy;
}

bool InventoryService::bulkUpdateStatus(const QList<qint64> &ids, const QString &status, QString *errorMessage) {
    DiamondRepository repo;
    bool ok = repo.bulkUpdateStatus(ids, status, errorMessage);
    if (ok) {
        AuditRepository audit;
        for (qint64 id : ids) {
            audit.logAction(id, QStringLiteral("Bulk Status Changed"), QStringLiteral("status"), QString(), status);
        }
    }
    return ok;
}

bool InventoryService::bulkAdjustPrice(const QList<qint64> &ids, double percent, QString *errorMessage) {
    DiamondRepository repo;
    bool ok = repo.bulkAdjustSellingPricePercent(ids, percent, errorMessage);
    if (ok) {
        AuditRepository audit;
        for (qint64 id : ids) {
            audit.logAction(id, QStringLiteral("Bulk Price Adjustment"), QStringLiteral("selling_price"), QString(), QStringLiteral("%1%").arg(percent));
        }
    }
    return ok;
}

bool InventoryService::bulkArchive(const QList<qint64> &ids, bool archive, QString *errorMessage) {
    DiamondRepository repo;
    return repo.bulkArchive(ids, archive, errorMessage);
}

QString InventoryService::generateNextReference(const QString &prefix) {
    DiamondRepository repo;
    int nextNum = 100;
    while (true) {
        QString candidate = QStringLiteral("%1%2").arg(prefix, QString::number(nextNum).rightJustified(5, QLatin1Char('0')));
        if (!repo.referenceExists(candidate)) {
            return candidate;
        }
        nextNum++;
    }
}
