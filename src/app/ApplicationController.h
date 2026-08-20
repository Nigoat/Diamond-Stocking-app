#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include "DiamondListModel.h"
#include "SupplierListModel.h"
#include "AppSettings.h"

class ApplicationController : public QObject {
    Q_OBJECT
    Q_PROPERTY(DiamondListModel* diamondModel READ diamondModel CONSTANT)
    Q_PROPERTY(SupplierListModel* supplierModel READ supplierModel CONSTANT)
    Q_PROPERTY(AppSettings* settings READ settings CONSTANT)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)
    Q_PROPERTY(QString appName READ appName CONSTANT)

public:
    explicit ApplicationController(QObject *parent = nullptr);
    ~ApplicationController() override = default;

    void initialize();

    DiamondListModel* diamondModel() { return &m_diamondModel; }
    SupplierListModel* supplierModel() { return &m_supplierModel; }
    AppSettings* settings() { return &AppSettings::instance(); }
    QString appVersion() const { return QStringLiteral("1.0.0"); }
    QString appName() const { return QStringLiteral("Diamond Inventory"); }

    Q_INVOKABLE bool saveDiamond(const QVariantMap &diamondData);
    Q_INVOKABLE bool archiveDiamond(qint64 id);
    Q_INVOKABLE bool restoreDiamond(qint64 id);
    Q_INVOKABLE bool toggleFavorite(qint64 id);
    Q_INVOKABLE bool deleteDiamondPermanently(qint64 id);
    Q_INVOKABLE QVariantMap duplicateDiamond(qint64 id);
    Q_INVOKABLE bool updateDiamondStatus(qint64 id, const QString &status);

    Q_INVOKABLE bool bulkUpdateStatus(const QVariantList &ids, const QString &status);
    Q_INVOKABLE bool bulkAdjustPrice(const QVariantList &ids, double percent);
    Q_INVOKABLE bool bulkArchive(const QVariantList &ids, bool archive);

    Q_INVOKABLE bool addDiamondImage(qint64 diamondId, const QString &filePath, const QString &imageType = QStringLiteral("main"));
    Q_INVOKABLE bool removeDiamondImage(qint64 imageId);
    Q_INVOKABLE bool setMainDiamondImage(qint64 diamondId, qint64 imageId);
    Q_INVOKABLE QVariantList getDiamondImages(qint64 diamondId);
    Q_INVOKABLE QVariantList getDiamondAuditLogs(qint64 diamondId);

    Q_INVOKABLE bool saveSupplier(const QVariantMap &supplierData);
    Q_INVOKABLE bool deleteSupplier(qint64 id);

    Q_INVOKABLE bool createBackup();
    Q_INVOKABLE bool restoreBackup(const QString &filePath);
    Q_INVOKABLE QVariantList listBackups();
    Q_INVOKABLE void openBackupsFolder();
    Q_INVOKABLE void openExportsFolder();

    Q_INVOKABLE bool exportCsv(const QString &filePath);
    Q_INVOKABLE bool exportPdf(const QString &filePath);
    Q_INVOKABLE bool printDiamondSheet(qint64 diamondId, const QString &outputPath);

    Q_INVOKABLE QVariantMap previewImportCsv(const QString &filePath);
    Q_INVOKABLE QVariantMap executeImportCsv(const QString &filePath, const QVariantMap &columnMap);

    Q_INVOKABLE QVariantMap getDashboardStats();
    Q_INVOKABLE QVariantMap getReportsBreakdown();

    Q_INVOKABLE void seedDemoData();
    Q_INVOKABLE QString generateNextReference(const QString &prefix = QStringLiteral("DMD-"));
    Q_INVOKABLE QString getDefaultExportPath(const QString &extension = QStringLiteral("csv"));
    Q_INVOKABLE QString getDefaultPrintPath(const QString &ref = QStringLiteral("diamond"));

    Q_INVOKABLE void showToast(const QString &type, const QString &message);

signals:
    void toastRequested(const QString &type, const QString &message);
    void inventoryModified();
    void suppliersModified();

private:
    DiamondListModel m_diamondModel;
    SupplierListModel m_supplierModel;
};

#endif
