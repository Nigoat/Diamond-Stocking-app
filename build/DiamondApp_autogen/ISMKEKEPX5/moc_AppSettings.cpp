/****************************************************************************
** Meta object code from reading C++ file 'AppSettings.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/AppSettings.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppSettings.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11AppSettingsE_t {};
} // unnamed namespace

template <> constexpr inline auto AppSettings::qt_create_metaobjectdata<qt_meta_tag_ZN11AppSettingsE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AppSettings",
        "themeChanged",
        "",
        "viewModeChanged",
        "storeInfoChanged",
        "currencyCodeChanged",
        "autoBackupIntervalChanged",
        "lastBackupDateChanged",
        "getUiSetting",
        "QVariant",
        "key",
        "defaultValue",
        "setUiSetting",
        "value",
        "getDatabaseSetting",
        "setDatabaseSetting",
        "theme",
        "viewMode",
        "storeName",
        "storeAddress",
        "storePhone",
        "storeEmail",
        "currencyCode",
        "autoBackupInterval",
        "lastBackupDate"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'themeChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'viewModeChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'storeInfoChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currencyCodeChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'autoBackupIntervalChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'lastBackupDateChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getUiSetting'
        QtMocHelpers::MethodData<QVariant(const QString &, const QVariant &) const>(8, 2, QMC::AccessPublic, 0x80000000 | 9, {{
            { QMetaType::QString, 10 }, { 0x80000000 | 9, 11 },
        }}),
        // Method 'getUiSetting'
        QtMocHelpers::MethodData<QVariant(const QString &) const>(8, 2, QMC::AccessPublic | QMC::MethodCloned, 0x80000000 | 9, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'setUiSetting'
        QtMocHelpers::MethodData<void(const QString &, const QVariant &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { 0x80000000 | 9, 13 },
        }}),
        // Method 'getDatabaseSetting'
        QtMocHelpers::MethodData<QString(const QString &, const QString &) const>(14, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
        }}),
        // Method 'getDatabaseSetting'
        QtMocHelpers::MethodData<QString(const QString &) const>(14, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::QString, {{
            { QMetaType::QString, 10 },
        }}),
        // Method 'setDatabaseSetting'
        QtMocHelpers::MethodData<void(const QString &, const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QString, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'theme'
        QtMocHelpers::PropertyData<QString>(16, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'viewMode'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'storeName'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'storeAddress'
        QtMocHelpers::PropertyData<QString>(19, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'storePhone'
        QtMocHelpers::PropertyData<QString>(20, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'storeEmail'
        QtMocHelpers::PropertyData<QString>(21, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'currencyCode'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'autoBackupInterval'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 4),
        // property 'lastBackupDate'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 5),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AppSettings, qt_meta_tag_ZN11AppSettingsE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AppSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AppSettingsE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AppSettingsE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11AppSettingsE_t>.metaTypes,
    nullptr
} };

void AppSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AppSettings *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->themeChanged(); break;
        case 1: _t->viewModeChanged(); break;
        case 2: _t->storeInfoChanged(); break;
        case 3: _t->currencyCodeChanged(); break;
        case 4: _t->autoBackupIntervalChanged(); break;
        case 5: _t->lastBackupDateChanged(); break;
        case 6: { QVariant _r = _t->getUiSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QVariant*>(_a[0]) = std::move(_r); }  break;
        case 7: { QVariant _r = _t->getUiSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QVariant*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setUiSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QVariant>>(_a[2]))); break;
        case 9: { QString _r = _t->getDatabaseSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->getDatabaseSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setDatabaseSetting((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::themeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::viewModeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::storeInfoChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::currencyCodeChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::autoBackupIntervalChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (AppSettings::*)()>(_a, &AppSettings::lastBackupDateChanged, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->theme(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->viewMode(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->storeName(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->storeAddress(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->storePhone(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->storeEmail(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->currencyCode(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->autoBackupInterval(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->lastBackupDate(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTheme(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->setViewMode(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setStoreName(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setStoreAddress(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->setStorePhone(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->setStoreEmail(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->setCurrencyCode(*reinterpret_cast<QString*>(_v)); break;
        case 7: _t->setAutoBackupInterval(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->setLastBackupDate(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *AppSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11AppSettingsE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void AppSettings::themeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppSettings::viewModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppSettings::storeInfoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AppSettings::currencyCodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AppSettings::autoBackupIntervalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AppSettings::lastBackupDateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
