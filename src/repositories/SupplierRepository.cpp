#include "SupplierRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

QList<Supplier> SupplierRepository::getAll(const QString &search) {
    QList<Supplier> list;
    if (!DatabaseManager::instance().isOpen()) return list;

    QString sql = QStringLiteral(
        "SELECT s.id, s.name, s.company, s.phone, s.email, s.address, s.country, s.notes, s.created_at, "
        "COUNT(d.id) AS diamond_count, "
        "COALESCE(SUM(d.purchase_price_cents), 0) AS total_cost_cents "
        "FROM suppliers s "
        "LEFT JOIN diamonds d ON d.supplier_id = s.id AND d.archived = 0 "
    );

    if (!search.trimmed().isEmpty()) {
        sql += QStringLiteral("WHERE s.name LIKE :search OR s.company LIKE :search OR s.email LIKE :search ");
    }

    sql += QStringLiteral("GROUP BY s.id ORDER BY s.name ASC");

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(sql);
    if (!search.trimmed().isEmpty()) {
        q.bindValue(QStringLiteral(":search"), QStringLiteral("%%1%").arg(search.trimmed()));
    }

    if (q.exec()) {
        while (q.next()) {
            Supplier s;
            s.setId(q.value(0).toLongLong());
            s.setName(q.value(1).toString());
            s.setCompany(q.value(2).toString());
            s.setPhone(q.value(3).toString());
            s.setEmail(q.value(4).toString());
            s.setAddress(q.value(5).toString());
            s.setCountry(q.value(6).toString());
            s.setNotes(q.value(7).toString());
            s.setCreatedAt(q.value(8).toString());
            s.setDiamondCount(q.value(9).toLongLong());
            s.setTotalCostCents(q.value(10).toLongLong());
            list.append(s);
        }
    }
    return list;
}

std::optional<Supplier> SupplierRepository::getById(qint64 id) {
    if (!DatabaseManager::instance().isOpen()) return std::nullopt;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "SELECT s.id, s.name, s.company, s.phone, s.email, s.address, s.country, s.notes, s.created_at, "
        "COUNT(d.id) AS diamond_count, "
        "COALESCE(SUM(d.purchase_price_cents), 0) AS total_cost_cents "
        "FROM suppliers s "
        "LEFT JOIN diamonds d ON d.supplier_id = s.id AND d.archived = 0 "
        "WHERE s.id = :id "
        "GROUP BY s.id"
    ));
    q.bindValue(QStringLiteral(":id"), id);

    if (q.exec() && q.next()) {
        Supplier s;
        s.setId(q.value(0).toLongLong());
        s.setName(q.value(1).toString());
        s.setCompany(q.value(2).toString());
        s.setPhone(q.value(3).toString());
        s.setEmail(q.value(4).toString());
        s.setAddress(q.value(5).toString());
        s.setCountry(q.value(6).toString());
        s.setNotes(q.value(7).toString());
        s.setCreatedAt(q.value(8).toString());
        s.setDiamondCount(q.value(9).toLongLong());
        s.setTotalCostCents(q.value(10).toLongLong());
        return s;
    }
    return std::nullopt;
}

bool SupplierRepository::insert(Supplier &supplier, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO suppliers (name, company, phone, email, address, country, notes, created_at) "
        "VALUES (:name, :company, :phone, :email, :address, :country, :notes, datetime('now', 'utc'))"
    ));
    q.bindValue(QStringLiteral(":name"), supplier.name());
    q.bindValue(QStringLiteral(":company"), supplier.company());
    q.bindValue(QStringLiteral(":phone"), supplier.phone());
    q.bindValue(QStringLiteral(":email"), supplier.email());
    q.bindValue(QStringLiteral(":address"), supplier.address());
    q.bindValue(QStringLiteral(":country"), supplier.country());
    q.bindValue(QStringLiteral(":notes"), supplier.notes());

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }

    supplier.setId(q.lastInsertId().toLongLong());
    return true;
}

bool SupplierRepository::update(const Supplier &supplier, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE suppliers SET name = :name, company = :company, phone = :phone, email = :email, "
        "address = :address, country = :country, notes = :notes WHERE id = :id"
    ));
    q.bindValue(QStringLiteral(":id"), supplier.id());
    q.bindValue(QStringLiteral(":name"), supplier.name());
    q.bindValue(QStringLiteral(":company"), supplier.company());
    q.bindValue(QStringLiteral(":phone"), supplier.phone());
    q.bindValue(QStringLiteral(":email"), supplier.email());
    q.bindValue(QStringLiteral(":address"), supplier.address());
    q.bindValue(QStringLiteral(":country"), supplier.country());
    q.bindValue(QStringLiteral(":notes"), supplier.notes());

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool SupplierRepository::remove(qint64 id, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM suppliers WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}
