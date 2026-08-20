#include "SupplierListModel.h"
#include "Money.h"

SupplierListModel::SupplierListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int SupplierListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(m_suppliers.size());
}

QVariant SupplierListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_suppliers.size()) {
        return QVariant();
    }

    const Supplier &s = m_suppliers.at(index.row());

    switch (role) {
    case IdRole: return s.id();
    case NameRole: return s.name();
    case CompanyRole: return s.company();
    case PhoneRole: return s.phone();
    case EmailRole: return s.email();
    case AddressRole: return s.address();
    case CountryRole: return s.country();
    case NotesRole: return s.notes();
    case CreatedAtRole: return s.createdAt();
    case DiamondCountRole: return s.diamondCount();
    case TotalCostCentsRole: return s.totalCostCents();
    case TotalCostFormattedRole: return Money::fromCents(s.totalCostCents()).formatted();
    default: return QVariant();
    }
}

QHash<int, QByteArray> SupplierListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "supplierId";
    roles[NameRole] = "name";
    roles[CompanyRole] = "company";
    roles[PhoneRole] = "phone";
    roles[EmailRole] = "email";
    roles[AddressRole] = "address";
    roles[CountryRole] = "country";
    roles[NotesRole] = "notes";
    roles[CreatedAtRole] = "createdAt";
    roles[DiamondCountRole] = "diamondCount";
    roles[TotalCostCentsRole] = "totalCostCents";
    roles[TotalCostFormattedRole] = "totalCostFormatted";
    return roles;
}

void SupplierListModel::setSearch(const QString &search) {
    if (m_search != search) {
        m_search = search;
        emit searchChanged();
        reload();
    }
}

void SupplierListModel::reload() {
    SupplierRepository repo;
    QList<Supplier> list = repo.getAll(m_search);

    beginResetModel();
    m_suppliers = list;
    endResetModel();
    emit countChanged();
}

QVariantMap SupplierListModel::getAt(int index) const {
    if (index >= 0 && index < m_suppliers.size()) {
        return m_suppliers.at(index).toVariantMap();
    }
    return QVariantMap();
}

QVariantMap SupplierListModel::getById(qint64 id) const {
    for (const auto &s : m_suppliers) {
        if (s.id() == id) {
            return s.toVariantMap();
        }
    }
    SupplierRepository repo;
    auto opt = repo.getById(id);
    if (opt.has_value()) {
        return opt.value().toVariantMap();
    }
    return QVariantMap();
}
