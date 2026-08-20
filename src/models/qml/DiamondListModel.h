#ifndef DIAMONDLISTMODEL_H
#define DIAMONDLISTMODEL_H

#include <QAbstractListModel>
#include <QSet>
#include "Diamond.h"
#include "DiamondRepository.h"

class DiamondListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(int selectedCount READ selectedCount NOTIFY selectedCountChanged)
    Q_PROPERTY(QString currentSearch READ currentSearch WRITE setSearch NOTIFY filterChanged)
    Q_PROPERTY(QString currentStatus READ currentStatus WRITE setStatus NOTIFY filterChanged)
    Q_PROPERTY(QString currentShape READ currentShape WRITE setShape NOTIFY filterChanged)
    Q_PROPERTY(QString currentColor READ currentColor WRITE setColor NOTIFY filterChanged)
    Q_PROPERTY(QString currentClarity READ currentClarity WRITE setClarity NOTIFY filterChanged)
    Q_PROPERTY(QString currentCut READ currentCut WRITE setCut NOTIFY filterChanged)
    Q_PROPERTY(QString currentLab READ currentLab WRITE setLab NOTIFY filterChanged)
    Q_PROPERTY(double minCarat READ minCarat WRITE setMinCarat NOTIFY filterChanged)
    Q_PROPERTY(double maxCarat READ maxCarat WRITE setMaxCarat NOTIFY filterChanged)
    Q_PROPERTY(double minPrice READ minPrice WRITE setMinPrice NOTIFY filterChanged)
    Q_PROPERTY(double maxPrice READ maxPrice WRITE setMaxPrice NOTIFY filterChanged)
    Q_PROPERTY(int hasImage READ hasImage WRITE setHasImage NOTIFY filterChanged)
    Q_PROPERTY(int hasCert READ hasCert WRITE setHasCert NOTIFY filterChanged)
    Q_PROPERTY(qint64 currentSupplierId READ currentSupplierId WRITE setSupplierId NOTIFY filterChanged)
    Q_PROPERTY(bool includeArchived READ includeArchived WRITE setIncludeArchived NOTIFY filterChanged)
    Q_PROPERTY(QString sortBy READ sortBy WRITE setSortBy NOTIFY sortChanged)
    Q_PROPERTY(bool sortAscending READ sortAscending WRITE setSortAscending NOTIFY sortChanged)

public:
    enum DiamondRoles {
        IdRole = Qt::UserRole + 1,
        ReferenceRole,
        SkuRole,
        BarcodeRole,
        NameRole,
        DescriptionRole,
        ShapeRole,
        CaratRole,
        ColorRole,
        ClarityRole,
        CutRole,
        PolishRole,
        SymmetryRole,
        FluorescenceRole,
        TablePercentageRole,
        DepthPercentageRole,
        MeasurementsRole,
        GirdleRole,
        CuletRole,
        CertNumRole,
        CertLabRole,
        CertDateRole,
        CertNotesRole,
        PurchaseCostCentsRole,
        SellingPriceCentsRole,
        DiscountPriceCentsRole,
        MinSellingPriceCentsRole,
        PurchaseCostFormattedRole,
        SellingPriceFormattedRole,
        DiscountPriceFormattedRole,
        MarginFormattedRole,
        MarginPercentageRole,
        StatusRole,
        LocationRole,
        LocationDetailsRole,
        SupplierIdRole,
        SupplierNameRole,
        IsFavoriteRole,
        ArchivedRole,
        CreatedAtRole,
        UpdatedAtRole,
        MainThumbnailRole,
        MainImageRole,
        ImageCountRole,
        SelectedRole
    };
    Q_ENUM(DiamondRoles)

    explicit DiamondListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;

    QString currentSearch() const { return m_criteria.search; }
    void setSearch(const QString &search);

    QString currentStatus() const { return m_criteria.status; }
    void setStatus(const QString &status);

    QString currentShape() const { return m_criteria.shape; }
    void setShape(const QString &shape);

    QString currentColor() const { return m_criteria.color; }
    void setColor(const QString &color);

    QString currentClarity() const { return m_criteria.clarity; }
    void setClarity(const QString &clarity);

    QString currentCut() const { return m_criteria.cut; }
    void setCut(const QString &cut);

    QString currentLab() const { return m_criteria.certificateLab; }
    void setLab(const QString &lab);

    double minCarat() const { return m_criteria.minCarat; }
    void setMinCarat(double val);

    double maxCarat() const { return m_criteria.maxCarat; }
    void setMaxCarat(double val);

    double minPrice() const { return static_cast<double>(m_criteria.minPriceCents) / 100.0; }
    void setMinPrice(double val);

    double maxPrice() const { return static_cast<double>(m_criteria.maxPriceCents) / 100.0; }
    void setMaxPrice(double val);

    int hasImage() const { return m_criteria.hasImage; }
    void setHasImage(int val);

    int hasCert() const { return m_criteria.hasCertificate; }
    void setHasCert(int val);

    qint64 currentSupplierId() const { return m_criteria.supplierId; }
    void setSupplierId(qint64 id);

    bool includeArchived() const { return m_criteria.includeArchived; }
    void setIncludeArchived(bool inc);

    QString sortBy() const { return m_criteria.sortBy; }
    void setSortBy(const QString &sort);

    bool sortAscending() const { return m_criteria.sortAscending; }
    void setSortAscending(bool asc);

    int selectedCount() const { return m_selectedIds.size(); }

    Q_INVOKABLE void reload();
    Q_INVOKABLE void resetFilters();
    Q_INVOKABLE void toggleSelection(qint64 id);
    Q_INVOKABLE void selectAll();
    Q_INVOKABLE void clearSelection();
    Q_INVOKABLE bool isSelected(qint64 id) const;
    Q_INVOKABLE QList<qint64> selectedIds() const;
    Q_INVOKABLE QVariantMap getAt(int index) const;
    Q_INVOKABLE QVariantMap getById(qint64 id) const;

    const DiamondFilterCriteria &criteria() const { return m_criteria; }

signals:
    void countChanged();
    void selectedCountChanged();
    void filterChanged();
    void sortChanged();

private:
    QList<Diamond> m_diamonds;
    QSet<qint64> m_selectedIds;
    DiamondFilterCriteria m_criteria;
};

#endif
