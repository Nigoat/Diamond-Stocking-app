#ifndef SUPPLIERREPOSITORY_H
#define SUPPLIERREPOSITORY_H

#include "Supplier.h"
#include <QList>
#include <optional>

class SupplierRepository {
public:
    SupplierRepository() = default;

    QList<Supplier> getAll(const QString &search = QString());
    std::optional<Supplier> getById(qint64 id);
    bool insert(Supplier &supplier, QString *errorMessage = nullptr);
    bool update(const Supplier &supplier, QString *errorMessage = nullptr);
    bool remove(qint64 id, QString *errorMessage = nullptr);
};

#endif
