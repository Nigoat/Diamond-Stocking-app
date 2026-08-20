#include "DiamondListModel.h"
#include "DiamondRepository.h"
#include <cmath>

DiamondListModel::DiamondListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_criteria.includeArchived = false;
    m_criteria.sortBy = QStringLiteral("created_at");
    m_criteria.sortAscending = false;
}

int DiamondListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(m_diamonds.size());
}

QVariant DiamondListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_diamonds.size()) {
        return QVariant();
    }

    const Diamond &d = m_diamonds.at(index.row());

    switch (role) {
    case IdRole: return d.id();
    case ReferenceRole: return d.reference();
    case SkuRole: return d.sku();
    case BarcodeRole: return d.barcode();
    case NameRole: return d.name();
    case DescriptionRole: return d.description();
    case ShapeRole: return d.shape();
    case CaratRole: return d.caratWeight();
    case ColorRole: return d.color();
    case ClarityRole: return d.clarity();
    case CutRole: return d.cut();
    case PolishRole: return d.polish();
    case SymmetryRole: return d.symmetry();
    case FluorescenceRole: return d.fluorescence();
    case TablePercentageRole: return d.tablePercentage();
    case DepthPercentageRole: return d.depthPercentage();
    case MeasurementsRole: return d.measurementsFormatted();
    case GirdleRole: return d.girdle();
    case CuletRole: return d.culet();
    case CertNumRole: return d.certificateNumber();
    case CertLabRole: return d.certificateLab();
    case CertDateRole: return d.certificateDate();
    case CertNotesRole: return d.certificateNotes();
    case PurchaseCostCentsRole: return d.purchasePriceCents();
    case SellingPriceCentsRole: return d.sellingPriceCents();
    case DiscountPriceCentsRole: return d.discountPriceCents();
    case MinSellingPriceCentsRole: return d.minSellingPriceCents();
    case PurchaseCostFormattedRole: return d.purchasePrice().formatted();
    case SellingPriceFormattedRole: return d.sellingPrice().formatted();
    case DiscountPriceFormattedRole: return d.discountPrice().formatted();
    case MarginFormattedRole: return d.margin().formatted();
    case MarginPercentageRole: return d.marginPercentage();
    case StatusRole: return d.status();
    case LocationRole: return d.location();
    case LocationDetailsRole: return d.locationDetails();
    case SupplierIdRole: return d.supplierId();
    case SupplierNameRole: return d.supplierName();
    case IsFavoriteRole: return d.isFavorite();
    case ArchivedRole: return d.archived();
    case CreatedAtRole: return d.createdAt();
    case UpdatedAtRole: return d.updatedAt();
    case MainThumbnailRole: return d.mainImageThumbnail();
    case MainImageRole: return d.mainImageFile();
    case ImageCountRole: return d.imageCount();
    case SelectedRole: return m_selectedIds.contains(d.id());
    default: return QVariant();
    }
}

bool DiamondListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_diamonds.size()) {
        return false;
    }

    if (role == SelectedRole) {
        qint64 id = m_diamonds.at(index.row()).id();
        bool select = value.toBool();
        if (select) {
            m_selectedIds.insert(id);
        } else {
            m_selectedIds.remove(id);
        }
        emit dataChanged(index, index, {SelectedRole});
        emit selectedCountChanged();
        return true;
    }
    return false;
}

QHash<int, QByteArray> DiamondListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "diamondId";
    roles[ReferenceRole] = "reference";
    roles[SkuRole] = "sku";
    roles[BarcodeRole] = "barcode";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[ShapeRole] = "shape";
    roles[CaratRole] = "carat";
    roles[ColorRole] = "color";
    roles[ClarityRole] = "clarity";
    roles[CutRole] = "cut";
    roles[PolishRole] = "polish";
    roles[SymmetryRole] = "symmetry";
    roles[FluorescenceRole] = "fluorescence";
    roles[TablePercentageRole] = "tablePercentage";
    roles[DepthPercentageRole] = "depthPercentage";
    roles[MeasurementsRole] = "measurements";
    roles[GirdleRole] = "girdle";
    roles[CuletRole] = "culet";
    roles[CertNumRole] = "certNum";
    roles[CertLabRole] = "certLab";
    roles[CertDateRole] = "certDate";
    roles[CertNotesRole] = "certNotes";
    roles[PurchaseCostCentsRole] = "purchaseCostCents";
    roles[SellingPriceCentsRole] = "sellingPriceCents";
    roles[DiscountPriceCentsRole] = "discountPriceCents";
    roles[MinSellingPriceCentsRole] = "minSellingPriceCents";
    roles[PurchaseCostFormattedRole] = "purchaseCostFormatted";
    roles[SellingPriceFormattedRole] = "sellingPriceFormatted";
    roles[DiscountPriceFormattedRole] = "discountPriceFormatted";
    roles[MarginFormattedRole] = "marginFormatted";
    roles[MarginPercentageRole] = "marginPercentage";
    roles[StatusRole] = "status";
    roles[LocationRole] = "location";
    roles[LocationDetailsRole] = "locationDetails";
    roles[SupplierIdRole] = "supplierId";
    roles[SupplierNameRole] = "supplierName";
    roles[IsFavoriteRole] = "isFavorite";
    roles[ArchivedRole] = "archived";
    roles[CreatedAtRole] = "createdAt";
    roles[UpdatedAtRole] = "updatedAt";
    roles[MainThumbnailRole] = "mainThumbnail";
    roles[MainImageRole] = "mainImage";
    roles[ImageCountRole] = "imageCount";
    roles[SelectedRole] = "selected";
    return roles;
}

void DiamondListModel::setSearch(const QString &search) {
    if (m_criteria.search != search) {
        m_criteria.search = search;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setStatus(const QString &status) {
    if (m_criteria.status != status) {
        m_criteria.status = status;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setShape(const QString &shape) {
    if (m_criteria.shape != shape) {
        m_criteria.shape = shape;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setColor(const QString &color) {
    if (m_criteria.color != color) {
        m_criteria.color = color;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setClarity(const QString &clarity) {
    if (m_criteria.clarity != clarity) {
        m_criteria.clarity = clarity;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setCut(const QString &cut) {
    if (m_criteria.cut != cut) {
        m_criteria.cut = cut;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setLab(const QString &lab) {
    if (m_criteria.certificateLab != lab) {
        m_criteria.certificateLab = lab;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setMinCarat(double val) {
    if (std::abs(m_criteria.minCarat - val) > 1e-4) {
        m_criteria.minCarat = val;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setMaxCarat(double val) {
    if (std::abs(m_criteria.maxCarat - val) > 1e-4) {
        m_criteria.maxCarat = val;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setMinPrice(double val) {
    qint64 cents = static_cast<qint64>(std::round(val * 100.0));
    if (m_criteria.minPriceCents != cents) {
        m_criteria.minPriceCents = cents;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setMaxPrice(double val) {
    qint64 cents = static_cast<qint64>(std::round(val * 100.0));
    if (m_criteria.maxPriceCents != cents) {
        m_criteria.maxPriceCents = cents;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setHasImage(int val) {
    if (m_criteria.hasImage != val) {
        m_criteria.hasImage = val;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setHasCert(int val) {
    if (m_criteria.hasCertificate != val) {
        m_criteria.hasCertificate = val;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setSupplierId(qint64 id) {
    if (m_criteria.supplierId != id) {
        m_criteria.supplierId = id;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setIncludeArchived(bool inc) {
    if (m_criteria.includeArchived != inc) {
        m_criteria.includeArchived = inc;
        emit filterChanged();
        reload();
    }
}

void DiamondListModel::setSortBy(const QString &sort) {
    if (m_criteria.sortBy != sort) {
        m_criteria.sortBy = sort;
        emit sortChanged();
        reload();
    }
}

void DiamondListModel::setSortAscending(bool asc) {
    if (m_criteria.sortAscending != asc) {
        m_criteria.sortAscending = asc;
        emit sortChanged();
        reload();
    }
}

void DiamondListModel::reload() {
    DiamondRepository repo;
    QList<Diamond> newList = repo.getList(m_criteria);

    beginResetModel();
    m_diamonds = newList;
    endResetModel();
    emit countChanged();
}

void DiamondListModel::resetFilters() {
    m_criteria = DiamondFilterCriteria();
    m_criteria.includeArchived = false;
    m_criteria.sortBy = QStringLiteral("created_at");
    m_criteria.sortAscending = false;
    emit filterChanged();
    emit sortChanged();
    reload();
}

void DiamondListModel::toggleSelection(qint64 id) {
    if (m_selectedIds.contains(id)) {
        m_selectedIds.remove(id);
    } else {
        m_selectedIds.insert(id);
    }

    for (int i = 0; i < m_diamonds.size(); ++i) {
        if (m_diamonds[i].id() == id) {
            QModelIndex idx = index(i, 0);
            emit dataChanged(idx, idx, {SelectedRole});
            break;
        }
    }
    emit selectedCountChanged();
}

void DiamondListModel::selectAll() {
    for (const auto &d : m_diamonds) {
        m_selectedIds.insert(d.id());
    }
    if (!m_diamonds.isEmpty()) {
        emit dataChanged(index(0, 0), index(m_diamonds.size() - 1, 0), {SelectedRole});
    }
    emit selectedCountChanged();
}

void DiamondListModel::clearSelection() {
    m_selectedIds.clear();
    if (!m_diamonds.isEmpty()) {
        emit dataChanged(index(0, 0), index(m_diamonds.size() - 1, 0), {SelectedRole});
    }
    emit selectedCountChanged();
}

bool DiamondListModel::isSelected(qint64 id) const {
    return m_selectedIds.contains(id);
}

QList<qint64> DiamondListModel::selectedIds() const {
    return m_selectedIds.values();
}

QVariantMap DiamondListModel::getAt(int index) const {
    if (index >= 0 && index < m_diamonds.size()) {
        return m_diamonds.at(index).toVariantMap();
    }
    return QVariantMap();
}

QVariantMap DiamondListModel::getById(qint64 id) const {
    for (const auto &d : m_diamonds) {
        if (d.id() == id) {
            return d.toVariantMap();
        }
    }
    DiamondRepository repo;
    auto opt = repo.getById(id);
    if (opt.has_value()) {
        return opt.value().toVariantMap();
    }
    return QVariantMap();
}
