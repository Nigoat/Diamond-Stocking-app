#include "AppSettings.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>

AppSettings::AppSettings(QObject *parent)
    : QObject(parent)
    , m_qsettings(QStringLiteral("DiamondStore"), QStringLiteral("DiamondInventory"))
{
}

AppSettings &AppSettings::instance() {
    static AppSettings inst;
    return inst;
}

QString AppSettings::theme() const {
    return m_qsettings.value(QStringLiteral("theme"), QStringLiteral("Dark")).toString();
}

void AppSettings::setTheme(const QString &theme) {
    if (this->theme() != theme) {
        m_qsettings.setValue(QStringLiteral("theme"), theme);
        emit themeChanged();
    }
}

QString AppSettings::viewMode() const {
    return m_qsettings.value(QStringLiteral("viewMode"), QStringLiteral("table")).toString();
}

void AppSettings::setViewMode(const QString &mode) {
    if (viewMode() != mode) {
        m_qsettings.setValue(QStringLiteral("viewMode"), mode);
        emit viewModeChanged();
    }
}

QString AppSettings::storeName() const {
    return getDatabaseSetting(QStringLiteral("store_name"), QStringLiteral("Maison du Diamant"));
}

void AppSettings::setStoreName(const QString &name) {
    setDatabaseSetting(QStringLiteral("store_name"), name);
    emit storeInfoChanged();
}

QString AppSettings::storeAddress() const {
    return getDatabaseSetting(QStringLiteral("store_address"), QStringLiteral("Boulevard Al Massira Al Khadra, Casablanca"));
}

void AppSettings::setStoreAddress(const QString &addr) {
    setDatabaseSetting(QStringLiteral("store_address"), addr);
    emit storeInfoChanged();
}

QString AppSettings::storePhone() const {
    return getDatabaseSetting(QStringLiteral("store_phone"), QStringLiteral("+212 522 998877"));
}

void AppSettings::setStorePhone(const QString &phone) {
    setDatabaseSetting(QStringLiteral("store_phone"), phone);
    emit storeInfoChanged();
}

QString AppSettings::storeEmail() const {
    return getDatabaseSetting(QStringLiteral("store_email"), QStringLiteral("contact@maison-diamant.ma"));
}

void AppSettings::setStoreEmail(const QString &email) {
    setDatabaseSetting(QStringLiteral("store_email"), email);
    emit storeInfoChanged();
}

QString AppSettings::currencyCode() const {
    return getDatabaseSetting(QStringLiteral("currency_code"), QStringLiteral("MAD"));
}

void AppSettings::setCurrencyCode(const QString &code) {
    setDatabaseSetting(QStringLiteral("currency_code"), code);
    emit currencyCodeChanged();
}

QString AppSettings::autoBackupInterval() const {
    return getDatabaseSetting(QStringLiteral("auto_backup_interval"), QStringLiteral("daily"));
}

void AppSettings::setAutoBackupInterval(const QString &interval) {
    setDatabaseSetting(QStringLiteral("auto_backup_interval"), interval);
    emit autoBackupIntervalChanged();
}

QString AppSettings::lastBackupDate() const {
    return getDatabaseSetting(QStringLiteral("last_backup_date"), QString());
}

void AppSettings::setLastBackupDate(const QString &date) {
    setDatabaseSetting(QStringLiteral("last_backup_date"), date);
    emit lastBackupDateChanged();
}

QVariant AppSettings::getUiSetting(const QString &key, const QVariant &defaultValue) const {
    return m_qsettings.value(key, defaultValue);
}

void AppSettings::setUiSetting(const QString &key, const QVariant &value) {
    m_qsettings.setValue(key, value);
}

QString AppSettings::getDatabaseSetting(const QString &key, const QString &defaultValue) const {
    if (!DatabaseManager::instance().isOpen()) {
        return defaultValue;
    }
    QSqlQuery query(DatabaseManager::instance().database());
    query.prepare(QStringLiteral("SELECT value FROM app_settings WHERE key = :key"));
    query.bindValue(QStringLiteral(":key"), key);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return defaultValue;
}

void AppSettings::setDatabaseSetting(const QString &key, const QString &value) {
    if (!DatabaseManager::instance().isOpen()) {
        return;
    }
    QSqlQuery query(DatabaseManager::instance().database());
    query.prepare(QStringLiteral(
        "INSERT INTO app_settings (key, value, updated_at) VALUES (:key, :value, datetime('now', 'utc')) "
        "ON CONFLICT(key) DO UPDATE SET value = excluded.value, updated_at = datetime('now', 'utc')"
    ));
    query.bindValue(QStringLiteral(":key"), key);
    query.bindValue(QStringLiteral(":value"), value);
    query.exec();
}
