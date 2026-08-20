#include "Supplier.h"

Supplier::Supplier()
    : m_id(0)
    , m_diamondCount(0)
    , m_totalCostCents(0)
{
}

QVariantMap Supplier::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("id")] = m_id;
    map[QStringLiteral("name")] = m_name;
    map[QStringLiteral("company")] = m_company;
    map[QStringLiteral("phone")] = m_phone;
    map[QStringLiteral("email")] = m_email;
    map[QStringLiteral("address")] = m_address;
    map[QStringLiteral("country")] = m_country;
    map[QStringLiteral("notes")] = m_notes;
    map[QStringLiteral("createdAt")] = m_createdAt;
    map[QStringLiteral("diamondCount")] = m_diamondCount;
    map[QStringLiteral("totalCostCents")] = m_totalCostCents;
    return map;
}

Supplier Supplier::fromVariantMap(const QVariantMap &map) {
    Supplier s;
    s.setId(map.value(QStringLiteral("id"), 0).toLongLong());
    s.setName(map.value(QStringLiteral("name")).toString());
    s.setCompany(map.value(QStringLiteral("company")).toString());
    s.setPhone(map.value(QStringLiteral("phone")).toString());
    s.setEmail(map.value(QStringLiteral("email")).toString());
    s.setAddress(map.value(QStringLiteral("address")).toString());
    s.setCountry(map.value(QStringLiteral("country")).toString());
    s.setNotes(map.value(QStringLiteral("notes")).toString());
    s.setCreatedAt(map.value(QStringLiteral("createdAt")).toString());
    s.setDiamondCount(map.value(QStringLiteral("diamondCount"), 0).toLongLong());
    s.setTotalCostCents(map.value(QStringLiteral("totalCostCents"), 0).toLongLong());
    return s;
}
