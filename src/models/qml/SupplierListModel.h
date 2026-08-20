#ifndef SUPPLIERLISTMODEL_H
#define SUPPLIERLISTMODEL_H

#include <QAbstractListModel>
#include "Supplier.h"
#include "SupplierRepository.h"

class SupplierListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)

public:
    enum SupplierRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        CompanyRole,
        PhoneRole,
        EmailRole,
        AddressRole,
        CountryRole,
        NotesRole,
        CreatedAtRole,
        DiamondCountRole,
        TotalCostCentsRole,
        TotalCostFormattedRole
    };
    Q_ENUM(SupplierRoles)

    explicit SupplierListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString search() const { return m_search; }
    void setSearch(const QString &search);

    Q_INVOKABLE void reload();
    Q_INVOKABLE QVariantMap getAt(int index) const;
    Q_INVOKABLE QVariantMap getById(qint64 id) const;

signals:
    void countChanged();
    void searchChanged();

private:
    QList<Supplier> m_suppliers;
    QString m_search;
};

#endif
