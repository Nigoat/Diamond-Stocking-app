#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <QString>
#include <QVariantMap>

class Supplier {
public:
    Supplier();

    qint64 id() const { return m_id; }
    void setId(qint64 id) { m_id = id; }

    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QString company() const { return m_company; }
    void setCompany(const QString &company) { m_company = company; }

    QString phone() const { return m_phone; }
    void setPhone(const QString &phone) { m_phone = phone; }

    QString email() const { return m_email; }
    void setEmail(const QString &email) { m_email = email; }

    QString address() const { return m_address; }
    void setAddress(const QString &address) { m_address = address; }

    QString country() const { return m_country; }
    void setCountry(const QString &country) { m_country = country; }

    QString notes() const { return m_notes; }
    void setNotes(const QString &notes) { m_notes = notes; }

    QString createdAt() const { return m_createdAt; }
    void setCreatedAt(const QString &createdAt) { m_createdAt = createdAt; }

    qint64 diamondCount() const { return m_diamondCount; }
    void setDiamondCount(qint64 count) { m_diamondCount = count; }

    qint64 totalCostCents() const { return m_totalCostCents; }
    void setTotalCostCents(qint64 cents) { m_totalCostCents = cents; }

    QVariantMap toVariantMap() const;
    static Supplier fromVariantMap(const QVariantMap &map);

private:
    qint64 m_id;
    QString m_name;
    QString m_company;
    QString m_phone;
    QString m_email;
    QString m_address;
    QString m_country;
    QString m_notes;
    QString m_createdAt;
    qint64 m_diamondCount;
    qint64 m_totalCostCents;
};

#endif
