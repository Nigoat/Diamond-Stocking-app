#include "DatabaseManager.h"
#include "DatabaseMigrations.h"
#include "AppPaths.h"
#include "FileUtils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QCoreApplication>

DatabaseManager::DatabaseManager()
    : m_connectionName(QStringLiteral("DiamondInventoryConnection"))
{
}

DatabaseManager::~DatabaseManager() {
    if (QCoreApplication::instance()) {
        close();
    }
}

DatabaseManager &DatabaseManager::instance() {
    static DatabaseManager inst;
    return inst;
}

bool DatabaseManager::initialize(const QString &dbPath) {
    QMutexLocker locker(&m_mutex);

    if (dbPath.isEmpty()) {
        m_dbPath = AppPaths::instance().databaseFilePath();
    } else {
        m_dbPath = dbPath;
    }

    QFileInfo fileInfo(m_dbPath);
    FileUtils::ensureDirExists(fileInfo.dir().absolutePath());

    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase existing = QSqlDatabase::database(m_connectionName);
        if (existing.isOpen()) {
            return true;
        }
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), m_connectionName);
    db.setDatabaseName(m_dbPath);

    if (!db.open()) {
        m_lastError = db.lastError().text();
        return false;
    }

    QSqlQuery pragmaWal(QStringLiteral("PRAGMA journal_mode = WAL;"), db);
    pragmaWal.exec();
    pragmaWal.finish();

    QSqlQuery pragmaFk(QStringLiteral("PRAGMA foreign_keys = ON;"), db);
    pragmaFk.exec();
    pragmaFk.finish();

    QSqlQuery pragmaSync(QStringLiteral("PRAGMA synchronous = NORMAL;"), db);
    pragmaSync.exec();
    pragmaSync.finish();

    QString migError;
    if (!DatabaseMigrations::runMigrations(db, &migError)) {
        m_lastError = migError;
        return false;
    }

    return true;
}

void DatabaseManager::close() {
    QMutexLocker locker(&m_mutex);
    if (QSqlDatabase::contains(m_connectionName)) {
        {
            QSqlDatabase db = QSqlDatabase::database(m_connectionName);
            if (db.isOpen()) {
                db.close();
            }
        }
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

bool DatabaseManager::isOpen() const {
    QMutexLocker locker(&m_mutex);
    if (!QSqlDatabase::contains(m_connectionName)) return false;
    return QSqlDatabase::database(m_connectionName).isOpen();
}

QSqlDatabase DatabaseManager::database() const {
    return QSqlDatabase::database(m_connectionName);
}

QString DatabaseManager::lastError() const {
    return m_lastError;
}

bool DatabaseManager::beginTransaction() {
    return database().transaction();
}

bool DatabaseManager::commitTransaction() {
    return database().commit();
}

bool DatabaseManager::rollbackTransaction() {
    return database().rollback();
}

bool DatabaseManager::seedDemoData() {
    QSqlDatabase db = database();
    QSqlQuery checkQuery(QStringLiteral("SELECT COUNT(*) FROM diamonds"), db);
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() > 0) {
            checkQuery.finish();
            return true;
        }
    }
    checkQuery.finish();

    QSqlQuery checkSuppliers(QStringLiteral("SELECT COUNT(*) FROM suppliers"), db);
    if (checkSuppliers.exec() && checkSuppliers.next()) {
        if (checkSuppliers.value(0).toInt() == 0) {
            QSqlQuery s1(db);
            s1.prepare(QStringLiteral("INSERT INTO suppliers (id, name, company, phone, email, address, country, notes) VALUES (:id, :name, :company, :phone, :email, :address, :country, :notes)"));
            s1.bindValue(QStringLiteral(":id"), 1);
            s1.bindValue(QStringLiteral(":name"), QStringLiteral("Karim Bennani"));
            s1.bindValue(QStringLiteral(":company"), QStringLiteral("Casablanca Diamonds SARL"));
            s1.bindValue(QStringLiteral(":phone"), QStringLiteral("+212 522 123456"));
            s1.bindValue(QStringLiteral(":email"), QStringLiteral("contact@casadiamonds.ma"));
            s1.bindValue(QStringLiteral(":address"), QStringLiteral("142 Boulevard d'Anfa"));
            s1.bindValue(QStringLiteral(":country"), QStringLiteral("Morocco"));
            s1.bindValue(QStringLiteral(":notes"), QStringLiteral("Primary local certified supplier"));
            s1.exec();
            s1.finish();

            QSqlQuery s2(db);
            s2.prepare(QStringLiteral("INSERT INTO suppliers (id, name, company, phone, email, address, country, notes) VALUES (:id, :name, :company, :phone, :email, :address, :country, :notes)"));
            s2.bindValue(QStringLiteral(":id"), 2);
            s2.bindValue(QStringLiteral(":name"), QStringLiteral("David & Sons Diamond Trading"));
            s2.bindValue(QStringLiteral(":company"), QStringLiteral("Antwerp Gem Trading Co."));
            s2.bindValue(QStringLiteral(":phone"), QStringLiteral("+32 3 234 5678"));
            s2.bindValue(QStringLiteral(":email"), QStringLiteral("orders@antwerpgem.be"));
            s2.bindValue(QStringLiteral(":address"), QStringLiteral("Hoveniersstraat 32"));
            s2.bindValue(QStringLiteral(":country"), QStringLiteral("Belgium"));
            s2.bindValue(QStringLiteral(":notes"), QStringLiteral("GIA certified natural diamonds"));
            s2.exec();
            s2.finish();

            QSqlQuery s3(db);
            s3.prepare(QStringLiteral("INSERT INTO suppliers (id, name, company, phone, email, address, country, notes) VALUES (:id, :name, :company, :phone, :email, :address, :country, :notes)"));
            s3.bindValue(QStringLiteral(":id"), 3);
            s3.bindValue(QStringLiteral(":name"), QStringLiteral("Atlas Gemological Imports"));
            s3.bindValue(QStringLiteral(":company"), QStringLiteral("Atlas Gems Marrakech"));
            s3.bindValue(QStringLiteral(":phone"), QStringLiteral("+212 524 987654"));
            s3.bindValue(QStringLiteral(":email"), QStringLiteral("info@atlasgems.ma"));
            s3.bindValue(QStringLiteral(":address"), QStringLiteral("45 Rue de la Liberte, Gueliz"));
            s3.bindValue(QStringLiteral(":country"), QStringLiteral("Morocco"));
            s3.bindValue(QStringLiteral(":notes"), QStringLiteral("High carat fancy shapes"));
            s3.exec();
            s3.finish();
        }
    }
    checkSuppliers.finish();

    struct DemoItem {
        QString ref;
        QString sku;
        QString barcode;
        QString name;
        QString desc;
        QString shape;
        double carat;
        QString color;
        QString clarity;
        QString cut;
        QString polish;
        QString symmetry;
        QString fluo;
        double table;
        double depth;
        double l;
        double w;
        double h;
        QString certNum;
        QString lab;
        QString certDate;
        qint64 purchase;
        qint64 sell;
        qint64 disc;
        qint64 minSell;
        QString status;
        QString loc;
        QString locDet;
        qint64 supplierId;
        bool isFav;
    };

    QList<DemoItem> items = {
        {
            QStringLiteral("DMD-00101"), QStringLiteral("SKU-RND-101"), QStringLiteral("611100010101"),
            QStringLiteral("Round Brilliant Solitaire"), QStringLiteral("Triple excellent round brilliant diamond with maximum fire and sparkle."),
            QStringLiteral("Round"), 1.05, QStringLiteral("D"), QStringLiteral("VVS1"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("None"),
            57.0, 61.5, 6.52, 6.55, 4.02,
            QStringLiteral("GIA-218491024"), QStringLiteral("GIA"), QStringLiteral("2025-11-15"),
            4800000, 6500000, 6200000, 5800000,
            QStringLiteral("Available"), QStringLiteral("Main Vault"), QStringLiteral("Tray A - Slot 1"), 2, true
        },
        {
            QStringLiteral("DMD-00102"), QStringLiteral("SKU-OVAL-102"), QStringLiteral("611100010102"),
            QStringLiteral("Oval Elegance Diamond"), QStringLiteral("Stunning elongated oval cut with high clarity and minimal bowtie effect."),
            QStringLiteral("Oval"), 1.52, QStringLiteral("F"), QStringLiteral("VS1"), QStringLiteral("Very Good"), QStringLiteral("Excellent"), QStringLiteral("Very Good"), QStringLiteral("Faint"),
            59.0, 63.2, 9.15, 6.42, 4.05,
            QStringLiteral("IGI-520194821"), QStringLiteral("IGI"), QStringLiteral("2025-12-02"),
            6200000, 8400000, 8000000, 7500000,
            QStringLiteral("Available"), QStringLiteral("Display Case 1"), QStringLiteral("Top Shelf / Ring Stand B"), 1, true
        },
        {
            QStringLiteral("DMD-00103"), QStringLiteral("SKU-PRIN-103"), QStringLiteral("611100010103"),
            QStringLiteral("Princess Cut Royale"), QStringLiteral("Classic square modified brilliant with sharp corners and intense brilliance."),
            QStringLiteral("Princess"), 0.95, QStringLiteral("G"), QStringLiteral("VS2"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("Very Good"), QStringLiteral("None"),
            68.0, 72.1, 5.40, 5.38, 3.88,
            QStringLiteral("GIA-639102488"), QStringLiteral("GIA"), QStringLiteral("2026-01-10"),
            2800000, 3900000, 3750000, 3400000,
            QStringLiteral("Reserved"), QStringLiteral("Safe Deposit"), QStringLiteral("Box #4"), 1, false
        },
        {
            QStringLiteral("DMD-00104"), QStringLiteral("SKU-EMR-104"), QStringLiteral("611100010104"),
            QStringLiteral("Emerald Cut Vintage"), QStringLiteral("Sophisticated step cut diamond with mesmerizing hall-of-mirrors effect."),
            QStringLiteral("Emerald"), 2.10, QStringLiteral("E"), QStringLiteral("VVS2"), QStringLiteral("Very Good"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("None"),
            64.0, 66.8, 8.60, 6.10, 4.07,
            QStringLiteral("HRD-22004819"), QStringLiteral("HRD"), QStringLiteral("2025-10-20"),
            11500000, 15800000, 15000000, 14000000,
            QStringLiteral("Available"), QStringLiteral("Main Vault"), QStringLiteral("Tray B - Slot 4"), 2, true
        },
        {
            QStringLiteral("DMD-00105"), QStringLiteral("SKU-CUSH-105"), QStringLiteral("611100010105"),
            QStringLiteral("Cushion Modified Brilliant"), QStringLiteral("Romantic pillow-shaped diamond with soft rounded corners and deep fire."),
            QStringLiteral("Cushion"), 1.25, QStringLiteral("H"), QStringLiteral("SI1"), QStringLiteral("Good"), QStringLiteral("Very Good"), QStringLiteral("Good"), QStringLiteral("Medium"),
            61.0, 65.4, 6.70, 6.35, 4.15,
            QStringLiteral("IGI-489102377"), QStringLiteral("IGI"), QStringLiteral("2026-02-05"),
            3400000, 4700000, 4500000, 4200000,
            QStringLiteral("Sold"), QStringLiteral("Store Archive"), QStringLiteral("Delivered to Customer Order #892"), 3, false
        },
        {
            QStringLiteral("DMD-00106"), QStringLiteral("SKU-PEAR-106"), QStringLiteral("611100010106"),
            QStringLiteral("Pear Shaped Teardrop"), QStringLiteral("Graceful pear cut with balanced proportions and sparkling teardrop tip."),
            QStringLiteral("Pear"), 0.85, QStringLiteral("G"), QStringLiteral("VS1"), QStringLiteral("Very Good"), QStringLiteral("Excellent"), QStringLiteral("Very Good"), QStringLiteral("None"),
            58.5, 62.8, 7.85, 5.12, 3.21,
            QStringLiteral("GIA-719382104"), QStringLiteral("GIA"), QStringLiteral("2026-01-22"),
            2400000, 3350000, 3200000, 2900000,
            QStringLiteral("Available"), QStringLiteral("Display Case 2"), QStringLiteral("Tray C - Slot 2"), 1, false
        },
        {
            QStringLiteral("DMD-00107"), QStringLiteral("SKU-RAD-107"), QStringLiteral("611100010107"),
            QStringLiteral("Radiant Cut Sparkler"), QStringLiteral("Vibrant hybrid combining emerald shape elegance with brilliant cut facet sparkle."),
            QStringLiteral("Radiant"), 1.70, QStringLiteral("D"), QStringLiteral("VS2"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("Excellent"), QStringLiteral("None"),
            66.0, 69.5, 7.45, 6.30, 4.38,
            QStringLiteral("GIA-839201948"), QStringLiteral("GIA"), QStringLiteral("2026-02-14"),
            7900000, 10800000, 10300000, 9600000,
            QStringLiteral("Available"), QStringLiteral("Main Vault"), QStringLiteral("Tray A - Slot 5"), 3, true
        },
        {
            QStringLiteral("DMD-00108"), QStringLiteral("SKU-MARQ-108"), QStringLiteral("611100010108"),
            QStringLiteral("Marquise Navette Diamond"), QStringLiteral("Dramatic football-shaped diamond maximizing carat spread and brilliance."),
            QStringLiteral("Marquise"), 1.12, QStringLiteral("I"), QStringLiteral("SI1"), QStringLiteral("Good"), QStringLiteral("Good"), QStringLiteral("Very Good"), QStringLiteral("Strong"),
            60.0, 63.0, 10.40, 5.20, 3.28,
            QStringLiteral("IGI-918237190"), QStringLiteral("IGI"), QStringLiteral("2025-09-18"),
            2600000, 3600000, 3450000, 3100000,
            QStringLiteral("Available"), QStringLiteral("Display Case 1"), QStringLiteral("Tray D - Slot 1"), 1, false
        }
    };

    db.transaction();
    for (const auto &item : items) {
        QSqlQuery q(db);
        q.prepare(QStringLiteral(
            "INSERT INTO diamonds ("
            "reference, sku, barcode, name, description, shape, carat_weight, color, clarity, cut, polish, symmetry, fluorescence,"
            "table_percentage, depth_percentage, length_mm, width_mm, height_mm, girdle, culet,"
            "certificate_number, certificate_lab, certificate_date,"
            "purchase_price_cents, selling_price_cents, discount_price_cents, min_selling_price_cents,"
            "status, location, location_details, supplier_id, is_favorite, archived"
            ") VALUES ("
            ":reference, :sku, :barcode, :name, :description, :shape, :carat_weight, :color, :clarity, :cut, :polish, :symmetry, :fluorescence,"
            ":table_percentage, :depth_percentage, :length_mm, :width_mm, :height_mm, :girdle, :culet,"
            ":certificate_number, :certificate_lab, :certificate_date,"
            ":purchase_price_cents, :selling_price_cents, :discount_price_cents, :min_selling_price_cents,"
            ":status, :location, :location_details, :supplier_id, :is_favorite, :archived"
            ")"
        ));
        q.bindValue(QStringLiteral(":reference"), item.ref);
        q.bindValue(QStringLiteral(":sku"), item.sku);
        q.bindValue(QStringLiteral(":barcode"), item.barcode);
        q.bindValue(QStringLiteral(":name"), item.name);
        q.bindValue(QStringLiteral(":description"), item.desc);
        q.bindValue(QStringLiteral(":shape"), item.shape);
        q.bindValue(QStringLiteral(":carat_weight"), item.carat);
        q.bindValue(QStringLiteral(":color"), item.color);
        q.bindValue(QStringLiteral(":clarity"), item.clarity);
        q.bindValue(QStringLiteral(":cut"), item.cut);
        q.bindValue(QStringLiteral(":polish"), item.polish);
        q.bindValue(QStringLiteral(":symmetry"), item.symmetry);
        q.bindValue(QStringLiteral(":fluorescence"), item.fluo);
        q.bindValue(QStringLiteral(":table_percentage"), item.table);
        q.bindValue(QStringLiteral(":depth_percentage"), item.depth);
        q.bindValue(QStringLiteral(":length_mm"), item.l);
        q.bindValue(QStringLiteral(":width_mm"), item.w);
        q.bindValue(QStringLiteral(":height_mm"), item.h);
        q.bindValue(QStringLiteral(":girdle"), QStringLiteral("Medium"));
        q.bindValue(QStringLiteral(":culet"), QStringLiteral("None"));
        q.bindValue(QStringLiteral(":certificate_number"), item.certNum);
        q.bindValue(QStringLiteral(":certificate_lab"), item.lab);
        q.bindValue(QStringLiteral(":certificate_date"), item.certDate);
        q.bindValue(QStringLiteral(":purchase_price_cents"), item.purchase);
        q.bindValue(QStringLiteral(":selling_price_cents"), item.sell);
        q.bindValue(QStringLiteral(":discount_price_cents"), item.disc);
        q.bindValue(QStringLiteral(":min_selling_price_cents"), item.minSell);
        q.bindValue(QStringLiteral(":status"), item.status);
        q.bindValue(QStringLiteral(":location"), item.loc);
        q.bindValue(QStringLiteral(":location_details"), item.locDet);
        q.bindValue(QStringLiteral(":supplier_id"), item.supplierId);
        q.bindValue(QStringLiteral(":is_favorite"), item.isFav ? 1 : 0);
        q.bindValue(QStringLiteral(":archived"), 0);
        q.exec();
        q.finish();
    }
    db.commit();
    return true;
}
