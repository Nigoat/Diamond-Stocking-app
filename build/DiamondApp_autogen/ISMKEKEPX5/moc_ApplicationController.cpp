/****************************************************************************
** Meta object code from reading C++ file 'ApplicationController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/ApplicationController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplicationController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN21ApplicationControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto ApplicationController::qt_create_metaobjectdata<qt_meta_tag_ZN21ApplicationControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ApplicationController",
        "toastRequested",
        "",
        "type",
        "message",
        "inventoryModified",
        "suppliersModified",
        "saveDiamond",
        "QVariantMap",
        "diamondData",
        "archiveDiamond",
        "id",
        "restoreDiamond",
        "toggleFavorite",
        "deleteDiamondPermanently",
        "duplicateDiamond",
        "updateDiamondStatus",
        "status",
        "bulkUpdateStatus",
        "QVariantList",
        "ids",
        "bulkAdjustPrice",
        "percent",
        "bulkArchive",
        "archive",
        "addDiamondImage",
        "diamondId",
        "filePath",
        "imageType",
        "removeDiamondImage",
        "imageId",
        "setMainDiamondImage",
        "getDiamondImages",
        "getDiamondAuditLogs",
        "saveSupplier",
        "supplierData",
        "deleteSupplier",
        "createBackup",
        "restoreBackup",
        "listBackups",
        "openBackupsFolder",
        "openExportsFolder",
        "exportCsv",
        "exportPdf",
        "printDiamondSheet",
        "outputPath",
        "previewImportCsv",
        "executeImportCsv",
        "columnMap",
        "getDashboardStats",
        "getReportsBreakdown",
        "seedDemoData",
        "generateNextReference",
        "prefix",
        "getDefaultExportPath",
        "extension",
        "getDefaultPrintPath",
        "ref",
        "showToast",
        "diamondModel",
        "DiamondListModel*",
        "supplierModel",
        "SupplierListModel*",
        "settings",
        "AppSettings*",
        "appVersion",
        "appName"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'toastRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'inventoryModified'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'suppliersModified'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'saveDiamond'
        QtMocHelpers::MethodData<bool(const QVariantMap &)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Method 'archiveDiamond'
        QtMocHelpers::MethodData<bool(qint64)>(10, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'restoreDiamond'
        QtMocHelpers::MethodData<bool(qint64)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'toggleFavorite'
        QtMocHelpers::MethodData<bool(qint64)>(13, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'deleteDiamondPermanently'
        QtMocHelpers::MethodData<bool(qint64)>(14, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'duplicateDiamond'
        QtMocHelpers::MethodData<QVariantMap(qint64)>(15, 2, QMC::AccessPublic, 0x80000000 | 8, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'updateDiamondStatus'
        QtMocHelpers::MethodData<bool(qint64, const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 }, { QMetaType::QString, 17 },
        }}),
        // Method 'bulkUpdateStatus'
        QtMocHelpers::MethodData<bool(const QVariantList &, const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 19, 20 }, { QMetaType::QString, 17 },
        }}),
        // Method 'bulkAdjustPrice'
        QtMocHelpers::MethodData<bool(const QVariantList &, double)>(21, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 19, 20 }, { QMetaType::Double, 22 },
        }}),
        // Method 'bulkArchive'
        QtMocHelpers::MethodData<bool(const QVariantList &, bool)>(23, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 19, 20 }, { QMetaType::Bool, 24 },
        }}),
        // Method 'addDiamondImage'
        QtMocHelpers::MethodData<bool(qint64, const QString &, const QString &)>(25, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 26 }, { QMetaType::QString, 27 }, { QMetaType::QString, 28 },
        }}),
        // Method 'addDiamondImage'
        QtMocHelpers::MethodData<bool(qint64, const QString &)>(25, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Bool, {{
            { QMetaType::LongLong, 26 }, { QMetaType::QString, 27 },
        }}),
        // Method 'removeDiamondImage'
        QtMocHelpers::MethodData<bool(qint64)>(29, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 30 },
        }}),
        // Method 'setMainDiamondImage'
        QtMocHelpers::MethodData<bool(qint64, qint64)>(31, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 26 }, { QMetaType::LongLong, 30 },
        }}),
        // Method 'getDiamondImages'
        QtMocHelpers::MethodData<QVariantList(qint64)>(32, 2, QMC::AccessPublic, 0x80000000 | 19, {{
            { QMetaType::LongLong, 26 },
        }}),
        // Method 'getDiamondAuditLogs'
        QtMocHelpers::MethodData<QVariantList(qint64)>(33, 2, QMC::AccessPublic, 0x80000000 | 19, {{
            { QMetaType::LongLong, 26 },
        }}),
        // Method 'saveSupplier'
        QtMocHelpers::MethodData<bool(const QVariantMap &)>(34, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { 0x80000000 | 8, 35 },
        }}),
        // Method 'deleteSupplier'
        QtMocHelpers::MethodData<bool(qint64)>(36, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 11 },
        }}),
        // Method 'createBackup'
        QtMocHelpers::MethodData<bool()>(37, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'restoreBackup'
        QtMocHelpers::MethodData<bool(const QString &)>(38, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'listBackups'
        QtMocHelpers::MethodData<QVariantList()>(39, 2, QMC::AccessPublic, 0x80000000 | 19),
        // Method 'openBackupsFolder'
        QtMocHelpers::MethodData<void()>(40, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'openExportsFolder'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'exportCsv'
        QtMocHelpers::MethodData<bool(const QString &)>(42, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'exportPdf'
        QtMocHelpers::MethodData<bool(const QString &)>(43, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'printDiamondSheet'
        QtMocHelpers::MethodData<bool(qint64, const QString &)>(44, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 26 }, { QMetaType::QString, 45 },
        }}),
        // Method 'previewImportCsv'
        QtMocHelpers::MethodData<QVariantMap(const QString &)>(46, 2, QMC::AccessPublic, 0x80000000 | 8, {{
            { QMetaType::QString, 27 },
        }}),
        // Method 'executeImportCsv'
        QtMocHelpers::MethodData<QVariantMap(const QString &, const QVariantMap &)>(47, 2, QMC::AccessPublic, 0x80000000 | 8, {{
            { QMetaType::QString, 27 }, { 0x80000000 | 8, 48 },
        }}),
        // Method 'getDashboardStats'
        QtMocHelpers::MethodData<QVariantMap()>(49, 2, QMC::AccessPublic, 0x80000000 | 8),
        // Method 'getReportsBreakdown'
        QtMocHelpers::MethodData<QVariantMap()>(50, 2, QMC::AccessPublic, 0x80000000 | 8),
        // Method 'seedDemoData'
        QtMocHelpers::MethodData<void()>(51, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'generateNextReference'
        QtMocHelpers::MethodData<QString(const QString &)>(52, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 53 },
        }}),
        // Method 'generateNextReference'
        QtMocHelpers::MethodData<QString()>(52, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString),
        // Method 'getDefaultExportPath'
        QtMocHelpers::MethodData<QString(const QString &)>(54, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 55 },
        }}),
        // Method 'getDefaultExportPath'
        QtMocHelpers::MethodData<QString()>(54, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString),
        // Method 'getDefaultPrintPath'
        QtMocHelpers::MethodData<QString(const QString &)>(56, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 57 },
        }}),
        // Method 'getDefaultPrintPath'
        QtMocHelpers::MethodData<QString()>(56, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString),
        // Method 'showToast'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(58, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'diamondModel'
        QtMocHelpers::PropertyData<DiamondListModel*>(59, 0x80000000 | 60, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'supplierModel'
        QtMocHelpers::PropertyData<SupplierListModel*>(61, 0x80000000 | 62, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'settings'
        QtMocHelpers::PropertyData<AppSettings*>(63, 0x80000000 | 64, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'appVersion'
        QtMocHelpers::PropertyData<QString>(65, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'appName'
        QtMocHelpers::PropertyData<QString>(66, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ApplicationController, qt_meta_tag_ZN21ApplicationControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ApplicationController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21ApplicationControllerE_t>.metaTypes,
    nullptr
} };

void ApplicationController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ApplicationController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->toastRequested((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->inventoryModified(); break;
        case 2: _t->suppliersModified(); break;
        case 3: { bool _r = _t->saveDiamond((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->archiveDiamond((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->restoreDiamond((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->toggleFavorite((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->deleteDiamondPermanently((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { QVariantMap _r = _t->duplicateDiamond((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->updateDiamondStatus((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->bulkUpdateStatus((*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->bulkAdjustPrice((*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->bulkArchive((*reinterpret_cast<std::add_pointer_t<QVariantList>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->addDiamondImage((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->addDiamondImage((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { bool _r = _t->removeDiamondImage((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->setMainDiamondImage((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<qint64>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { QVariantList _r = _t->getDiamondImages((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 18: { QVariantList _r = _t->getDiamondAuditLogs((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->saveSupplier((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->deleteSupplier((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->createBackup();
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { bool _r = _t->restoreBackup((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { QVariantList _r = _t->listBackups();
            if (_a[0]) *reinterpret_cast<QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->openBackupsFolder(); break;
        case 25: _t->openExportsFolder(); break;
        case 26: { bool _r = _t->exportCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->exportPdf((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->printDiamondSheet((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { QVariantMap _r = _t->previewImportCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 30: { QVariantMap _r = _t->executeImportCsv((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 31: { QVariantMap _r = _t->getDashboardStats();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 32: { QVariantMap _r = _t->getReportsBreakdown();
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->seedDemoData(); break;
        case 34: { QString _r = _t->generateNextReference((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 35: { QString _r = _t->generateNextReference();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 36: { QString _r = _t->getDefaultExportPath((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 37: { QString _r = _t->getDefaultExportPath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 38: { QString _r = _t->getDefaultPrintPath((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 39: { QString _r = _t->getDefaultPrintPath();
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->showToast((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ApplicationController::*)(const QString & , const QString & )>(_a, &ApplicationController::toastRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApplicationController::*)()>(_a, &ApplicationController::inventoryModified, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApplicationController::*)()>(_a, &ApplicationController::suppliersModified, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AppSettings* >(); break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DiamondListModel* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SupplierListModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<DiamondListModel**>(_v) = _t->diamondModel(); break;
        case 1: *reinterpret_cast<SupplierListModel**>(_v) = _t->supplierModel(); break;
        case 2: *reinterpret_cast<AppSettings**>(_v) = _t->settings(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->appVersion(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->appName(); break;
        default: break;
        }
    }
}

const QMetaObject *ApplicationController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApplicationController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApplicationController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 41;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ApplicationController::toastRequested(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ApplicationController::inventoryModified()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ApplicationController::suppliersModified()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
