CREATE TABLE IF NOT EXISTS suppliers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    company TEXT,
    phone TEXT,
    email TEXT,
    address TEXT,
    country TEXT,
    notes TEXT,
    created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))
);

CREATE TABLE IF NOT EXISTS diamonds (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    reference TEXT NOT NULL UNIQUE,
    sku TEXT,
    barcode TEXT,
    name TEXT NOT NULL,
    description TEXT,
    shape TEXT NOT NULL DEFAULT 'Round',
    carat_weight REAL NOT NULL DEFAULT 0.0,
    color TEXT NOT NULL DEFAULT 'G',
    clarity TEXT NOT NULL DEFAULT 'VS1',
    cut TEXT NOT NULL DEFAULT 'Excellent',
    polish TEXT DEFAULT 'Excellent',
    symmetry TEXT DEFAULT 'Very Good',
    fluorescence TEXT DEFAULT 'None',
    fluorescence_color TEXT,
    table_percentage REAL DEFAULT 0.0,
    depth_percentage REAL DEFAULT 0.0,
    length_mm REAL DEFAULT 0.0,
    width_mm REAL DEFAULT 0.0,
    height_mm REAL DEFAULT 0.0,
    girdle TEXT,
    culet TEXT,
    certificate_number TEXT,
    certificate_lab TEXT DEFAULT 'None',
    certificate_date TEXT,
    certificate_url TEXT,
    certificate_notes TEXT,
    purchase_price_cents INTEGER NOT NULL DEFAULT 0,
    selling_price_cents INTEGER NOT NULL DEFAULT 0,
    discount_price_cents INTEGER NOT NULL DEFAULT 0,
    min_selling_price_cents INTEGER NOT NULL DEFAULT 0,
    status TEXT NOT NULL DEFAULT 'Available',
    location TEXT DEFAULT 'Store',
    location_details TEXT,
    supplier_id INTEGER,
    is_favorite INTEGER NOT NULL DEFAULT 0,
    archived INTEGER NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),
    updated_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),
    FOREIGN KEY (supplier_id) REFERENCES suppliers(id) ON DELETE SET NULL
);

CREATE TABLE IF NOT EXISTS diamond_images (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    diamond_id INTEGER NOT NULL,
    file_path TEXT NOT NULL,
    thumbnail_path TEXT NOT NULL,
    image_type TEXT NOT NULL DEFAULT 'main',
    sort_order INTEGER NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT (datetime('now', 'utc')),
    FOREIGN KEY (diamond_id) REFERENCES diamonds(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS audit_log (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    diamond_id INTEGER,
    action TEXT NOT NULL,
    field_name TEXT,
    old_value TEXT,
    new_value TEXT,
    timestamp TEXT NOT NULL DEFAULT (datetime('now', 'utc')),
    FOREIGN KEY (diamond_id) REFERENCES diamonds(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS app_settings (
    key TEXT PRIMARY KEY,
    value TEXT NOT NULL,
    updated_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))
);

CREATE TABLE IF NOT EXISTS schema_migrations (
    version INTEGER PRIMARY KEY,
    applied_at TEXT NOT NULL DEFAULT (datetime('now', 'utc'))
);
