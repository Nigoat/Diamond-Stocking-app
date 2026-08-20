/****************************************************************************
** Meta object code from reading C++ file 'SupplierListModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/models/qml/SupplierListModel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SupplierListModel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17SupplierListModelE_t {};
} // unnamed namespace

template <> constexpr inline auto SupplierListModel::qt_create_metaobjectdata<qt_meta_tag_ZN17SupplierListModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SupplierListModel",
        "countChanged",
        "",
        "searchChanged",
        "reload",
        "getAt",
        "QVariantMap",
        "index",
        "getById",
        "id",
        "count",
        "search",
        "SupplierRoles",
        "IdRole",
        "NameRole",
        "CompanyRole",
        "PhoneRole",
        "EmailRole",
        "AddressRole",
        "CountryRole",
        "NotesRole",
        "CreatedAtRole",
        "DiamondCountRole",
        "TotalCostCentsRole",
        "TotalCostFormattedRole"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'countChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reload'
        QtMocHelpers::MethodData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getAt'
        QtMocHelpers::MethodData<QVariantMap(int) const>(5, 2, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::Int, 7 },
        }}),
        // Method 'getById'
        QtMocHelpers::MethodData<QVariantMap(qint64) const>(8, 2, QMC::AccessPublic, 0x80000000 | 6, {{
            { QMetaType::LongLong, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'count'
        QtMocHelpers::PropertyData<int>(10, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'search'
        QtMocHelpers::PropertyData<QString>(11, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'SupplierRoles'
        QtMocHelpers::EnumData<enum SupplierRoles>(12, 12, QMC::EnumFlags{}).add({
            {   13, SupplierRoles::IdRole },
            {   14, SupplierRoles::NameRole },
            {   15, SupplierRoles::CompanyRole },
            {   16, SupplierRoles::PhoneRole },
            {   17, SupplierRoles::EmailRole },
            {   18, SupplierRoles::AddressRole },
            {   19, SupplierRoles::CountryRole },
            {   20, SupplierRoles::NotesRole },
            {   21, SupplierRoles::CreatedAtRole },
            {   22, SupplierRoles::DiamondCountRole },
            {   23, SupplierRoles::TotalCostCentsRole },
            {   24, SupplierRoles::TotalCostFormattedRole },
        }),
    };
    return QtMocHelpers::metaObjectData<SupplierListModel, qt_meta_tag_ZN17SupplierListModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SupplierListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SupplierListModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SupplierListModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17SupplierListModelE_t>.metaTypes,
    nullptr
} };

void SupplierListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SupplierListModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->searchChanged(); break;
        case 2: _t->reload(); break;
        case 3: { QVariantMap _r = _t->getAt((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariantMap _r = _t->getById((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SupplierListModel::*)()>(_a, &SupplierListModel::countChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SupplierListModel::*)()>(_a, &SupplierListModel::searchChanged, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->rowCount(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->search(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setSearch(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *SupplierListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SupplierListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SupplierListModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SupplierListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SupplierListModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SupplierListModel::searchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
