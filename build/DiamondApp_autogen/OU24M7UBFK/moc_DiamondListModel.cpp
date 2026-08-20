/****************************************************************************
** Meta object code from reading C++ file 'DiamondListModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/models/qml/DiamondListModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DiamondListModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16DiamondListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto DiamondListModel::qt_create_metaobjectdata<qt_meta_tag_ZN16DiamondListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DiamondListModel",
        "countChanged",
        "",
        "selectedCountChanged",
        "filterChanged",
        "sortChanged",
        "reload",
        "resetFilters",
        "toggleSelection",
        "id",
        "selectAll",
        "clearSelection",
        "isSelected",
        "selectedIds",
        "QList<qint64>",
        "getAt",
        "QVariantMap",
        "index",
        "getById",
        "count",
        "selectedCount",
        "currentSearch",
        "currentStatus",
        "currentShape",
        "currentColor",
        "currentClarity",
        "currentCut",
        "currentLab",
        "minCarat",
        "maxCarat",
        "minPrice",
        "maxPrice",
        "hasImage",
        "hasCert",
        "currentSupplierId",
        "includeArchived",
        "sortBy",
        "sortAscending",
        "DiamondRoles",
        "IdRole",
        "ReferenceRole",
        "SkuRole",
        "BarcodeRole",
        "NameRole",
        "DescriptionRole",
        "ShapeRole",
        "CaratRole",
        "ColorRole",
        "ClarityRole",
        "CutRole",
        "PolishRole",
        "SymmetryRole",
        "FluorescenceRole",
        "TablePercentageRole",
        "DepthPercentageRole",
        "MeasurementsRole",
        "GirdleRole",
        "CuletRole",
        "CertNumRole",
        "CertLabRole",
        "CertDateRole",
        "CertNotesRole",
        "PurchaseCostCentsRole",
        "SellingPriceCentsRole",
        "DiscountPriceCentsRole",
        "MinSellingPriceCentsRole",
        "PurchaseCostFormattedRole",
        "SellingPriceFormattedRole",
        "DiscountPriceFormattedRole",
        "MarginFormattedRole",
        "MarginPercentageRole",
        "StatusRole",
        "LocationRole",
        "LocationDetailsRole",
        "SupplierIdRole",
        "SupplierNameRole",
        "IsFavoriteRole",
        "ArchivedRole",
        "CreatedAtRole",
        "UpdatedAtRole",
        "MainThumbnailRole",
        "MainImageRole",
        "ImageCountRole",
        "SelectedRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'countChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'selectedCountChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filterChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sortChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'resetFilters'
        QtMocHelpers::MethodData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'toggleSelection'
        QtMocHelpers::MethodData<void(qint64)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 9 },
        }}),
        // Method 'selectAll'
        QtMocHelpers::MethodData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'clearSelection'
        QtMocHelpers::MethodData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'isSelected'
        QtMocHelpers::MethodData<bool(qint64) const>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::LongLong, 9 },
        }}),
        // Method 'selectedIds'
        QtMocHelpers::MethodData<QList<qint64>() const>(13, 2, QMC::AccessPublic, 0x80000000 | 14),
        // Method 'getAt'
        QtMocHelpers::MethodData<QVariantMap(int) const>(15, 2, QMC::AccessPublic, 0x80000000 | 16, {{
            { QMetaType::Int, 17 },
        }}),
        // Method 'getById'
        QtMocHelpers::MethodData<QVariantMap(qint64) const>(18, 2, QMC::AccessPublic, 0x80000000 | 16, {{
            { QMetaType::LongLong, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'count'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'selectedCount'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'currentSearch'
        QtMocHelpers::PropertyData<QString>(21, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentStatus'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentShape'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentColor'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentClarity'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentCut'
        QtMocHelpers::PropertyData<QString>(26, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'currentLab'
        QtMocHelpers::PropertyData<QString>(27, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'minCarat'
        QtMocHelpers::PropertyData<double>(28, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'maxCarat'
        QtMocHelpers::PropertyData<double>(29, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'minPrice'
        QtMocHelpers::PropertyData<double>(30, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'maxPrice'
        QtMocHelpers::PropertyData<double>(31, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'hasImage'
        QtMocHelpers::PropertyData<int>(32, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'hasCert'
        QtMocHelpers::PropertyData<int>(33, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'currentSupplierId'
        QtMocHelpers::PropertyData<qint64>(34, QMetaType::LongLong, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'includeArchived'
        QtMocHelpers::PropertyData<bool>(35, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'sortBy'
        QtMocHelpers::PropertyData<QString>(36, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'sortAscending'
        QtMocHelpers::PropertyData<bool>(37, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'DiamondRoles'
        QtMocHelpers::EnumData<enum DiamondRoles>(38, 38, QMC::EnumFlags{}).add({
            {   39, DiamondRoles::IdRole },
            {   40, DiamondRoles::ReferenceRole },
            {   41, DiamondRoles::SkuRole },
            {   42, DiamondRoles::BarcodeRole },
            {   43, DiamondRoles::NameRole },
            {   44, DiamondRoles::DescriptionRole },
            {   45, DiamondRoles::ShapeRole },
            {   46, DiamondRoles::CaratRole },
            {   47, DiamondRoles::ColorRole },
            {   48, DiamondRoles::ClarityRole },
            {   49, DiamondRoles::CutRole },
            {   50, DiamondRoles::PolishRole },
            {   51, DiamondRoles::SymmetryRole },
            {   52, DiamondRoles::FluorescenceRole },
            {   53, DiamondRoles::TablePercentageRole },
            {   54, DiamondRoles::DepthPercentageRole },
            {   55, DiamondRoles::MeasurementsRole },
            {   56, DiamondRoles::GirdleRole },
            {   57, DiamondRoles::CuletRole },
            {   58, DiamondRoles::CertNumRole },
            {   59, DiamondRoles::CertLabRole },
            {   60, DiamondRoles::CertDateRole },
            {   61, DiamondRoles::CertNotesRole },
            {   62, DiamondRoles::PurchaseCostCentsRole },
            {   63, DiamondRoles::SellingPriceCentsRole },
            {   64, DiamondRoles::DiscountPriceCentsRole },
            {   65, DiamondRoles::MinSellingPriceCentsRole },
            {   66, DiamondRoles::PurchaseCostFormattedRole },
            {   67, DiamondRoles::SellingPriceFormattedRole },
            {   68, DiamondRoles::DiscountPriceFormattedRole },
            {   69, DiamondRoles::MarginFormattedRole },
            {   70, DiamondRoles::MarginPercentageRole },
            {   71, DiamondRoles::StatusRole },
            {   72, DiamondRoles::LocationRole },
            {   73, DiamondRoles::LocationDetailsRole },
            {   74, DiamondRoles::SupplierIdRole },
            {   75, DiamondRoles::SupplierNameRole },
            {   76, DiamondRoles::IsFavoriteRole },
            {   77, DiamondRoles::ArchivedRole },
            {   78, DiamondRoles::CreatedAtRole },
            {   79, DiamondRoles::UpdatedAtRole },
            {   80, DiamondRoles::MainThumbnailRole },
            {   81, DiamondRoles::MainImageRole },
            {   82, DiamondRoles::ImageCountRole },
            {   83, DiamondRoles::SelectedRole },
        }),
    };
    return QtMocHelpers::metaObjectData<DiamondListModel, qt_meta_tag_ZN16DiamondListModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DiamondListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16DiamondListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16DiamondListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16DiamondListModelE_t>.metaTypes,
    nullptr
} };

void DiamondListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DiamondListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->selectedCountChanged(); break;
        case 2: _t->filterChanged(); break;
        case 3: _t->sortChanged(); break;
        case 4: _t->reload(); break;
        case 5: _t->resetFilters(); break;
        case 6: _t->toggleSelection((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 7: _t->selectAll(); break;
        case 8: _t->clearSelection(); break;
        case 9: { bool _r = _t->isSelected((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { QList<qint64> _r = _t->selectedIds();
            if (_a[0]) *reinterpret_cast<QList<qint64>*>(_a[0]) = std::move(_r); }  break;
        case 11: { QVariantMap _r = _t->getAt((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 12: { QVariantMap _r = _t->getById((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DiamondListModel::*)()>(_a, &DiamondListModel::countChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondListModel::*)()>(_a, &DiamondListModel::selectedCountChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondListModel::*)()>(_a, &DiamondListModel::filterChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (DiamondListModel::*)()>(_a, &DiamondListModel::sortChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->rowCount(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->selectedCount(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->currentSearch(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->currentStatus(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->currentShape(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->currentColor(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->currentClarity(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->currentCut(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->currentLab(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->minCarat(); break;
        case 10: *reinterpret_cast<double*>(_v) = _t->maxCarat(); break;
        case 11: *reinterpret_cast<double*>(_v) = _t->minPrice(); break;
        case 12: *reinterpret_cast<double*>(_v) = _t->maxPrice(); break;
        case 13: *reinterpret_cast<int*>(_v) = _t->hasImage(); break;
        case 14: *reinterpret_cast<int*>(_v) = _t->hasCert(); break;
        case 15: *reinterpret_cast<qint64*>(_v) = _t->currentSupplierId(); break;
        case 16: *reinterpret_cast<bool*>(_v) = _t->includeArchived(); break;
        case 17: *reinterpret_cast<QString*>(_v) = _t->sortBy(); break;
        case 18: *reinterpret_cast<bool*>(_v) = _t->sortAscending(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setSearch(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setStatus(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setShape(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setColor(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setClarity(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setCut(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setLab(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->setMinCarat(*reinterpret_cast<double*>(_v)); break;
        case 10: _t->setMaxCarat(*reinterpret_cast<double*>(_v)); break;
        case 11: _t->setMinPrice(*reinterpret_cast<double*>(_v)); break;
        case 12: _t->setMaxPrice(*reinterpret_cast<double*>(_v)); break;
        case 13: _t->setHasImage(*reinterpret_cast<int*>(_v)); break;
        case 14: _t->setHasCert(*reinterpret_cast<int*>(_v)); break;
        case 15: _t->setSupplierId(*reinterpret_cast<qint64*>(_v)); break;
        case 16: _t->setIncludeArchived(*reinterpret_cast<bool*>(_v)); break;
        case 17: _t->setSortBy(*reinterpret_cast<QString*>(_v)); break;
        case 18: _t->setSortAscending(*reinterpret_cast<bool*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *DiamondListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DiamondListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16DiamondListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int DiamondListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void DiamondListModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DiamondListModel::selectedCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DiamondListModel::filterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DiamondListModel::sortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
