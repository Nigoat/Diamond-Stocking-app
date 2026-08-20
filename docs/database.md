# Database Schema & Storage

## Storage Location

Data is stored under standard user application data paths:

- **Linux:** `~/.local/share/DiamondStore/Diamond Inventory/database/inventory.db`
- **Windows:** `%LOCALAPPDATA%\DiamondStore\Diamond Inventory\database\inventory.db`

## Tables

### 1. `diamonds`

| Column | Type | Description |
|---|---|---|
| `id` | INTEGER PRIMARY KEY | Auto-increment unique ID |
| `reference` | TEXT NOT NULL UNIQUE | Store reference (e.g. DMD-00101) |
| `sku` | TEXT | SKU code |
| `barcode` | TEXT | Barcode or QR code string |
| `name` | TEXT NOT NULL | Diamond title/name |
| `description` | TEXT | Detailed notes |
| `shape` | TEXT NOT NULL | Shape (Round, Princess, Oval, etc.) |
| `carat_weight` | REAL NOT NULL | Weight in carats |
| `color` | TEXT NOT NULL | Color grade (D-M) |
| `clarity` | TEXT NOT NULL | Clarity grade (FL-I3) |
| `cut` | TEXT | Cut grade |
| `polish` | TEXT | Polish grade |
| `symmetry` | TEXT | Symmetry grade |
| `fluorescence` | TEXT | Fluorescence intensity |
| `fluorescence_color`| TEXT | Fluorescence color |
| `table_percentage` | REAL | Table percentage |
| `depth_percentage` | REAL | Depth percentage |
| `length_mm` | REAL | Length in mm |
| `width_mm` | REAL | Width in mm |
| `height_mm` | REAL | Height in mm |
| `girdle` | TEXT | Girdle description |
| `culet` | TEXT | Culet description |
| `certificate_number`| TEXT | Certificate number |
| `certificate_lab` | TEXT | Lab (GIA, IGI, HRD, GCAL, None) |
| `certificate_date` | TEXT | Date on certificate |
| `purchase_price_cents` | INTEGER | Purchase cost in MAD cents |
| `selling_price_cents` | INTEGER | Selling price in MAD cents |
| `discount_price_cents` | INTEGER | Discounted selling price in MAD cents |
| `min_selling_price_cents`| INTEGER | Minimum acceptable selling price |
| `status` | TEXT NOT NULL | Status (Available, Reserved, Sold, etc.) |
| `location` | TEXT | Storage location (Store, Main Vault, etc.) |
| `location_details` | TEXT | Tray, slot, or drawer |
| `supplier_id` | INTEGER | Foreign key to `suppliers(id)` |
| `is_favorite` | INTEGER | 1 if favorite, 0 otherwise |
| `archived` | INTEGER | 1 if archived, 0 otherwise |
| `created_at` | TEXT | ISO timestamp |
| `updated_at` | TEXT | ISO timestamp |

### 2. `suppliers`

| Column | Type | Description |
|---|---|---|
| `id` | INTEGER PRIMARY KEY | Auto-increment unique ID |
| `name` | TEXT NOT NULL | Supplier contact name |
| `company` | TEXT | Company name |
| `phone` | TEXT | Telephone |
| `email` | TEXT | Email address |
| `address` | TEXT | Physical address |
| `country` | TEXT | Country |
| `notes` | TEXT | Notes |
| `created_at` | TEXT | ISO timestamp |

### 3. `diamond_images`

| Column | Type | Description |
|---|---|---|
| `id` | INTEGER PRIMARY KEY | Unique ID |
| `diamond_id` | INTEGER NOT NULL | Foreign key to `diamonds(id)` |
| `file_path` | TEXT NOT NULL | Managed local image path |
| `thumbnail_path` | TEXT NOT NULL | 256x256 scaled thumbnail path |
| `image_type` | TEXT NOT NULL | Type (`main`, `side`, `certificate`) |
| `sort_order` | INTEGER | Display order |
| `created_at` | TEXT | ISO timestamp |

### 4. `audit_log`

| Column | Type | Description |
|---|---|---|
| `id` | INTEGER PRIMARY KEY | Unique ID |
| `diamond_id` | INTEGER | Foreign key to `diamonds(id)` |
| `action` | TEXT NOT NULL | Action description |
| `field_name` | TEXT | Modified field name |
| `old_value` | TEXT | Previous value |
| `new_value` | TEXT | New value |
| `timestamp` | TEXT NOT NULL | ISO timestamp |

### 5. `app_settings`

| Column | Type | Description |
|---|---|---|
| `key` | TEXT PRIMARY KEY | Setting key |
| `value` | TEXT NOT NULL | Setting value |
| `updated_at` | TEXT | ISO timestamp |
