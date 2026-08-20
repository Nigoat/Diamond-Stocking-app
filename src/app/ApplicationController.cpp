#include "ApplicationController.h"
#include "InventoryService.h"
#include "ImageService.h"
#include "BackupService.h"
#include "ExportService.h"
#include "ImportService.h"
#include "ReportService.h"
#include "PrintService.h"
#include "SupplierRepository.h"
#include "AuditRepository.h"
#include "AppPaths.h"
#include "DateUtils.h"
#include "DatabaseManager.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

ApplicationController::ApplicationController(QObject *parent)
    : QObject(parent)
{
}

void ApplicationController::initialize() {
    m_diamondModel.reload();
    m_supplierModel.reload();
    BackupService::instance().checkAndPerformAutoBackup();
}

bool ApplicationController::saveDiamond(const QVariantMap &diamondData) {
    Diamond d = Diamond::fromVariantMap(diamondData);
    QString error;
    bool success = false;

    if (d.id() <= 0) {
        success = InventoryService::instance().addDiamond(d, &error);
        if (success) {
            emit toastRequested(QStringLiteral("success"), QStringLiteral("Diamond added successfully: %1").arg(d.reference()));
        } else {
            emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to add diamond: %1").arg(error));
        }
    } else {
        success = InventoryService::instance().updateDiamond(d, &error);
        if (success) {
            emit toastRequested(QStringLiteral("success"), QStringLiteral("Diamond updated successfully: %1").arg(d.reference()));
        } else {
            emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to update diamond: %1").arg(error));
        }
    }

    if (success) {
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
    }
    return success;
}

bool ApplicationController::archiveDiamond(qint64 id) {
    QString error;
    bool ok = InventoryService::instance().archiveDiamond(id, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("info"), QStringLiteral("Diamond archived."));
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to archive diamond: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::restoreDiamond(qint64 id) {
    QString error;
    bool ok = InventoryService::instance().restoreDiamond(id, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Diamond restored."));
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to restore diamond: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::toggleFavorite(qint64 id) {
    QString error;
    bool ok = InventoryService::instance().toggleFavorite(id, &error);
    if (ok) {
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), error);
    }
    return ok;
}

bool ApplicationController::deleteDiamondPermanently(qint64 id) {
    QString error;
    bool ok = InventoryService::instance().deletePermanently(id, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("info"), QStringLiteral("Diamond record deleted permanently."));
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to delete diamond: %1").arg(error));
    }
    return ok;
}

QVariantMap ApplicationController::duplicateDiamond(qint64 id) {
    QString error;
    auto opt = InventoryService::instance().duplicateDiamond(id, &error);
    if (opt.has_value()) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Diamond duplicated as %1").arg(opt.value().reference()));
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
        return opt.value().toVariantMap();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to duplicate: %1").arg(error));
        return QVariantMap();
    }
}

bool ApplicationController::updateDiamondStatus(qint64 id, const QString &status) {
    DiamondRepository repo;
    QString error;
    bool ok = repo.setStatus(id, status, &error);
    if (ok) {
        AuditRepository audit;
        audit.logAction(id, QStringLiteral("Status Changed"), QStringLiteral("status"), QString(), status);
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Status changed to %1").arg(status));
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to update status: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::bulkUpdateStatus(const QVariantList &ids, const QString &status) {
    QList<qint64> list;
    for (const auto &v : ids) {
        list.append(v.toLongLong());
    }
    QString error;
    bool ok = InventoryService::instance().bulkUpdateStatus(list, status, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Updated %1 diamonds to %2").arg(QString::number(list.size()), status));
        m_diamondModel.clearSelection();
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Bulk update failed: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::bulkAdjustPrice(const QVariantList &ids, double percent) {
    QList<qint64> list;
    for (const auto &v : ids) {
        list.append(v.toLongLong());
    }
    QString error;
    bool ok = InventoryService::instance().bulkAdjustPrice(list, percent, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Adjusted prices for %1 diamonds by %2%").arg(QString::number(list.size()), QString::number(percent)));
        m_diamondModel.clearSelection();
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Bulk price adjustment failed: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::bulkArchive(const QVariantList &ids, bool archive) {
    QList<qint64> list;
    for (const auto &v : ids) {
        list.append(v.toLongLong());
    }
    QString error;
    bool ok = InventoryService::instance().bulkArchive(list, archive, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("info"), QStringLiteral("%1 %2 diamonds").arg(archive ? QStringLiteral("Archived") : QStringLiteral("Restored"), QString::number(list.size())));
        m_diamondModel.clearSelection();
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Bulk action failed: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::addDiamondImage(qint64 diamondId, const QString &filePath, const QString &imageType) {
    QString error;
    auto opt = ImageService::instance().saveImageForDiamond(diamondId, filePath, imageType, &error);
    if (opt.has_value()) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Image uploaded and processed."));
        m_diamondModel.reload();
        emit inventoryModified();
        return true;
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to add image: %1").arg(error));
        return false;
    }
}

bool ApplicationController::removeDiamondImage(qint64 imageId) {
    QString error;
    bool ok = ImageService::instance().removeImage(imageId, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("info"), QStringLiteral("Image removed."));
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to remove image: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::setMainDiamondImage(qint64 diamondId, qint64 imageId) {
    QString error;
    bool ok = ImageService::instance().setMainImage(diamondId, imageId, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Primary image updated."));
        m_diamondModel.reload();
        emit inventoryModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to set primary image: %1").arg(error));
    }
    return ok;
}

QVariantList ApplicationController::getDiamondImages(qint64 diamondId) {
    QVariantList list;
    QList<DiamondImage> imgs = ImageService::instance().getDiamondImages(diamondId);
    for (const auto &img : imgs) {
        list.append(img.toVariantMap());
    }
    return list;
}

QVariantList ApplicationController::getDiamondAuditLogs(qint64 diamondId) {
    QVariantList list;
    AuditRepository repo;
    QList<AuditLog> logs = repo.getByDiamondId(diamondId);
    for (const auto &log : logs) {
        list.append(log.toVariantMap());
    }
    return list;
}

bool ApplicationController::saveSupplier(const QVariantMap &supplierData) {
    Supplier s = Supplier::fromVariantMap(supplierData);
    SupplierRepository repo;
    QString error;
    bool success = false;

    if (s.id() <= 0) {
        success = repo.insert(s, &error);
        if (success) {
            emit toastRequested(QStringLiteral("success"), QStringLiteral("Supplier added: %1").arg(s.name()));
        } else {
            emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to add supplier: %1").arg(error));
        }
    } else {
        success = repo.update(s, &error);
        if (success) {
            emit toastRequested(QStringLiteral("success"), QStringLiteral("Supplier updated: %1").arg(s.name()));
        } else {
            emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to update supplier: %1").arg(error));
        }
    }

    if (success) {
        m_supplierModel.reload();
        m_diamondModel.reload();
        emit suppliersModified();
    }
    return success;
}

bool ApplicationController::deleteSupplier(qint64 id) {
    SupplierRepository repo;
    QString error;
    bool ok = repo.remove(id, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("info"), QStringLiteral("Supplier removed."));
        m_supplierModel.reload();
        m_diamondModel.reload();
        emit suppliersModified();
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to remove supplier: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::createBackup() {
    QString createdPath;
    QString error;
    bool ok = BackupService::instance().createBackup(&createdPath, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Backup created successfully."));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to create backup: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::restoreBackup(const QString &filePath) {
    QString error;
    bool ok = BackupService::instance().restoreBackup(filePath, &error);
    if (ok) {
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
        emit suppliersModified();
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Database restored successfully."));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Restore failed: %1").arg(error));
    }
    return ok;
}

QVariantList ApplicationController::listBackups() {
    QVariantList list;
    QList<BackupInfo> backups = BackupService::instance().listBackups();
    for (const auto &b : backups) {
        list.append(b.toVariantMap());
    }
    return list;
}

void ApplicationController::openBackupsFolder() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(AppPaths::instance().backupsDir()));
}

void ApplicationController::openExportsFolder() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(AppPaths::instance().exportsDir()));
}

bool ApplicationController::exportCsv(const QString &filePath) {
    QString target = filePath;
    if (target.isEmpty()) {
        target = getDefaultExportPath(QStringLiteral("csv"));
    }
    QString error;
    bool ok = ExportService::instance().exportToCsv(target, m_diamondModel.criteria(), &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Exported CSV to: %1").arg(target));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Export failed: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::exportPdf(const QString &filePath) {
    QString target = filePath;
    if (target.isEmpty()) {
        target = getDefaultExportPath(QStringLiteral("pdf"));
    }
    QString error;
    bool ok = ExportService::instance().exportToPdf(target, m_diamondModel.criteria(), &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Exported PDF to: %1").arg(target));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("PDF Export failed: %1").arg(error));
    }
    return ok;
}

bool ApplicationController::printDiamondSheet(qint64 diamondId, const QString &outputPath) {
    QString target = outputPath;
    if (target.isEmpty()) {
        DiamondRepository repo;
        auto opt = repo.getById(diamondId);
        QString ref = opt.has_value() ? opt.value().reference() : QStringLiteral("diamond");
        target = getDefaultPrintPath(ref);
    }
    QString error;
    bool ok = PrintService::instance().printDiamondSpecSheet(diamondId, target, &error);
    if (ok) {
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Spec sheet printed to: %1").arg(target));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Failed to print spec sheet: %1").arg(error));
    }
    return ok;
}

QVariantMap ApplicationController::previewImportCsv(const QString &filePath) {
    return ImportService::instance().previewCsv(filePath).toVariantMap();
}

QVariantMap ApplicationController::executeImportCsv(const QString &filePath, const QVariantMap &columnMap) {
    auto res = ImportService::instance().executeImport(filePath, columnMap);
    if (res.success) {
        m_diamondModel.reload();
        m_supplierModel.reload();
        emit inventoryModified();
        emit toastRequested(QStringLiteral("success"), QStringLiteral("Imported %1 diamonds successfully.").arg(QString::number(res.importedCount)));
    } else {
        emit toastRequested(QStringLiteral("error"), QStringLiteral("Import completed with %1 errors.").arg(QString::number(res.errorCount)));
    }
    return res.toVariantMap();
}

QVariantMap ApplicationController::getDashboardStats() {
    return ReportService::instance().getDashboardStats().toVariantMap();
}

QVariantMap ApplicationController::getReportsBreakdown() {
    return ReportService::instance().getReportsBreakdown();
}

void ApplicationController::seedDemoData() {
    DatabaseManager::instance().seedDemoData();
    m_diamondModel.reload();
    m_supplierModel.reload();
    emit inventoryModified();
    emit suppliersModified();
    emit toastRequested(QStringLiteral("success"), QStringLiteral("Demo data loaded."));
}

QString ApplicationController::generateNextReference(const QString &prefix) {
    return InventoryService::instance().generateNextReference(prefix);
}

QString ApplicationController::getDefaultExportPath(const QString &extension) {
    QString ts = DateUtils::formatTimestampForFilename();
    return AppPaths::instance().exportsDir() + QStringLiteral("/diamond_inventory_%1.%2").arg(ts, extension);
}

QString ApplicationController::getDefaultPrintPath(const QString &ref) {
    QString ts = DateUtils::formatTimestampForFilename();
    return AppPaths::instance().exportsDir() + QStringLiteral("/spec_sheet_%1_%2.pdf").arg(ref, ts);
}

void ApplicationController::showToast(const QString &type, const QString &message) {
    emit toastRequested(type, message);
}
