#include "DatabaseMigrations.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>

int DatabaseMigrations::currentVersion(QSqlDatabase &db) {
    QSqlQuery checkQuery(db);
    if (!checkQuery.exec(QStringLiteral("SELECT name FROM sqlite_master WHERE type='table' AND name='schema_migrations'"))) {
        return 0;
    }
    if (!checkQuery.next()) {
        checkQuery.finish();
        return 0;
    }
    checkQuery.finish();

    QSqlQuery versionQuery(db);
    if (versionQuery.exec(QStringLiteral("SELECT MAX(version) FROM schema_migrations")) && versionQuery.next()) {
        int v = versionQuery.value(0).toInt();
        versionQuery.finish();
        return v;
    }
    return 0;
}

QString DatabaseMigrations::getMigrationSql(int version) {
    if (version == 1) {
        return QStringLiteral(
            "CREATE TABLE IF NOT EXISTS suppliers ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "company TEXT,"
            "phone TEXT,"
            "email TEXT,"
            "address TEXT,"
            "country TEXT,"
            "notes TEXT,"
            "created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))"
            ");"

            "CREATE TABLE IF NOT EXISTS diamonds ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "reference TEXT NOT NULL UNIQUE,"
            "sku TEXT,"
            "barcode TEXT,"
            "name TEXT NOT NULL,"
            "description TEXT,"
            "shape TEXT NOT NULL DEFAULT 'Round',"
            "carat_weight REAL NOT NULL DEFAULT 0.0,"
            "color TEXT NOT NULL DEFAULT 'G',"
            "clarity TEXT NOT NULL DEFAULT 'VS1',"
            "cut TEXT NOT NULL DEFAULT 'Excellent',"
            "polish TEXT DEFAULT 'Excellent',"
            "symmetry TEXT DEFAULT 'Very Good',"
            "fluorescence TEXT DEFAULT 'None',"
            "fluorescence_color TEXT,"
            "table_percentage REAL DEFAULT 0.0,"
            "depth_percentage REAL DEFAULT 0.0,"
            "length_mm REAL DEFAULT 0.0,"
            "width_mm REAL DEFAULT 0.0,"
            "height_mm REAL DEFAULT 0.0,"
            "girdle TEXT,"
            "culet TEXT,"
            "certificate_number TEXT,"
            "certificate_lab TEXT DEFAULT 'None',"
            "certificate_date TEXT,"
            "certificate_url TEXT,"
            "certificate_notes TEXT,"
            "purchase_price_cents INTEGER NOT NULL DEFAULT 0,"
            "selling_price_cents INTEGER NOT NULL DEFAULT 0,"
            "discount_price_cents INTEGER NOT NULL DEFAULT 0,"
            "min_selling_price_cents INTEGER NOT NULL DEFAULT 0,"
            "status TEXT NOT NULL DEFAULT 'Available',"
            "location TEXT DEFAULT 'Store',"
            "location_details TEXT,"
            "supplier_id INTEGER,"
            "is_favorite INTEGER NOT NULL DEFAULT 0,"
            "archived INTEGER NOT NULL DEFAULT 0,"
            "created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),"
            "updated_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),"
            "FOREIGN KEY (supplier_id) REFERENCES suppliers(id) ON DELETE SET NULL"
            ");"

            "CREATE TABLE IF NOT EXISTS diamond_images ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "diamond_id INTEGER NOT NULL,"
            "file_path TEXT NOT NULL,"
            "thumbnail_path TEXT NOT NULL,"
            "image_type TEXT NOT NULL DEFAULT 'main',"
            "sort_order INTEGER NOT NULL DEFAULT 0,"
            "created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),"
            "FOREIGN KEY (diamond_id) REFERENCES diamonds(id) ON DELETE CASCADE"
            ");"

            "CREATE TABLE IF NOT EXISTS audit_log ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "diamond_id INTEGER,"
            "action TEXT NOT NULL,"
            "field_name TEXT,"
            "old_value TEXT,"
            "new_value TEXT,"
            "timestamp TEXT NOT NULL DEFAULT (datetime('now', 'utc')),"
            "FOREIGN KEY (diamond_id) REFERENCES diamonds(id) ON DELETE CASCADE"
            ");"

            "CREATE TABLE IF NOT EXISTS app_settings ("
            "key TEXT PRIMARY KEY,"
            "value TEXT NOT NULL,"
            "updated_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))"
            ");"

            "CREATE TABLE IF NOT EXISTS schema_migrations ("
            "version INTEGER PRIMARY KEY,"
            "applied_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))"
            ");"
        );
    } else if (version == 2) {
        return QStringLiteral(
            "CREATE INDEX IF NOT EXISTS idx_diamonds_ref ON diamonds(reference);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_name ON diamonds(name);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_status ON diamonds(status);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_shape ON diamonds(shape);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_carat ON diamonds(carat_weight);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_color ON diamonds(color);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_clarity ON diamonds(clarity);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_supplier ON diamonds(supplier_id);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_archived ON diamonds(archived);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_favorite ON diamonds(is_favorite);"
            "CREATE INDEX IF NOT EXISTS idx_diamonds_cert_num ON diamonds(certificate_number);"
            "CREATE INDEX IF NOT EXISTS idx_diamond_images_diamond_id ON diamond_images(diamond_id);"
            "CREATE INDEX IF NOT EXISTS idx_audit_log_diamond_id ON audit_log(diamond_id);"
        );
    }
    return QString();
}

bool DatabaseMigrations::executeMigrationScript(QSqlDatabase &db, int version, const QString &sql, QString *errorMessage) {
    if (sql.trimmed().isEmpty()) return true;

    if (!db.transaction()) {
        if (errorMessage) *errorMessage = db.lastError().text();
        return false;
    }

    const QStringList statements = sql.split(QStringLiteral(";"), Qt::SkipEmptyParts);
    for (const QString &stmt : statements) {
        QString trimmed = stmt.trimmed();
        if (trimmed.isEmpty()) continue;

        QSqlQuery query(db);
        if (!query.exec(trimmed)) {
            if (errorMessage) *errorMessage = query.lastError().text();
            query.finish();
            db.rollback();
            return false;
        }
        query.finish();
    }

    {
        QSqlQuery recordQuery(db);
        recordQuery.prepare(QStringLiteral("INSERT INTO schema_migrations (version, applied_at) VALUES (:version, datetime('now', 'utc'))"));
        recordQuery.bindValue(QStringLiteral(":version"), version);
        if (!recordQuery.exec()) {
            if (errorMessage) *errorMessage = recordQuery.lastError().text();
            recordQuery.finish();
            db.rollback();
            return false;
        }
        recordQuery.finish();
    }

    if (!db.commit()) {
        if (errorMessage) *errorMessage = db.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseMigrations::runMigrations(QSqlDatabase &db, QString *errorMessage) {
    int curVer = currentVersion(db);
    const int targetVersion = 2;

    for (int ver = curVer + 1; ver <= targetVersion; ++ver) {
        QString sql = getMigrationSql(ver);
        if (!executeMigrationScript(db, ver, sql, errorMessage)) {
            return false;
        }
    }
    return true;
}
