#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QSettings>

class AppSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString viewMode READ viewMode WRITE setViewMode NOTIFY viewModeChanged)
    Q_PROPERTY(QString storeName READ storeName WRITE setStoreName NOTIFY storeInfoChanged)
    Q_PROPERTY(QString storeAddress READ storeAddress WRITE setStoreAddress NOTIFY storeInfoChanged)
    Q_PROPERTY(QString storePhone READ storePhone WRITE setStorePhone NOTIFY storeInfoChanged)
    Q_PROPERTY(QString storeEmail READ storeEmail WRITE setStoreEmail NOTIFY storeInfoChanged)
    Q_PROPERTY(QString currencyCode READ currencyCode WRITE setCurrencyCode NOTIFY currencyCodeChanged)
    Q_PROPERTY(QString autoBackupInterval READ autoBackupInterval WRITE setAutoBackupInterval NOTIFY autoBackupIntervalChanged)
    Q_PROPERTY(QString lastBackupDate READ lastBackupDate WRITE setLastBackupDate NOTIFY lastBackupDateChanged)

public:
    static AppSettings &instance();

    QString theme() const;
    void setTheme(const QString &theme);

    QString viewMode() const;
    void setViewMode(const QString &mode);

    QString storeName() const;
    void setStoreName(const QString &name);

    QString storeAddress() const;
    void setStoreAddress(const QString &addr);

    QString storePhone() const;
    void setStorePhone(const QString &phone);

    QString storeEmail() const;
    void setStoreEmail(const QString &email);

    QString currencyCode() const;
    void setCurrencyCode(const QString &code);

    QString autoBackupInterval() const;
    void setAutoBackupInterval(const QString &interval);

    QString lastBackupDate() const;
    void setLastBackupDate(const QString &date);

    Q_INVOKABLE QVariant getUiSetting(const QString &key, const QVariant &defaultValue = QVariant()) const;
    Q_INVOKABLE void setUiSetting(const QString &key, const QVariant &value);

    Q_INVOKABLE QString getDatabaseSetting(const QString &key, const QString &defaultValue = QString()) const;
    Q_INVOKABLE void setDatabaseSetting(const QString &key, const QString &value);

signals:
    void themeChanged();
    void viewModeChanged();
    void storeInfoChanged();
    void currencyCodeChanged();
    void autoBackupIntervalChanged();
    void lastBackupDateChanged();

private:
    explicit AppSettings(QObject *parent = nullptr);
    ~AppSettings() override = default;
    AppSettings(const AppSettings &) = delete;
    AppSettings &operator=(const AppSettings &) = delete;

    QSettings m_qsettings;
};

#endif
