# Diamond Inventory & Stock Management

A desktop diamond inventory and stock management application designed for diamond and jewelry stores. Built with **C++17, Qt 6, Qt Quick/QML, SQLite, and CMake**.

## Key Features

- **Instant Multi-Field Search:** Real-time, debounced search across reference, diamond name, certificate number, supplier, shape, color, clarity, notes, and barcode.
- **Moroccan Dirham (MAD) Financial Tracking:** Exact minor-unit integer arithmetic for purchase costs, selling prices, discounts, minimum prices, profit margin, and profit percentage.
- **Stock Status Management:** Clear visual indicators for Available, Reserved, Sold, Unavailable, and Returned items.
- **High-Performance Table & Card Grid Views:** Toggle between customizable tabular data and rich card galleries.
- **Local Managed Image Storage:** Automatic 256x256 thumbnail generation with primary photo selection and image gallery.
- **Suppliers Directory:** Supplier profiles linked to diamond inventory with aggregate purchase statistics.
- **Dashboard & Business Analytics:** Real-time inventory overview, total stock valuation, potential margins, and distribution charts (shape, color, clarity, status, supplier).
- **Import & Export:** Full UTF-8 CSV import with column header mapping, live data validation, and batch transactions. Export inventory to CSV or printable PDF reports.
- **Professional Printing:** Generation of Diamond Specification Dossiers and Inventory Summary PDFs.
- **Automated Database Backups:** Timestamped SQLite snapshots with safety backups before restores and automatic retention policies.
- **Offline-First & Local Data Persistence:** Zero cloud dependencies, zero external network calls.

---

## Architecture

The project maintains strict separation of concerns across distinct layers:

```text
Diamond/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── docs/
│   ├── architecture.md
│   ├── database.md
│   ├── build-linux.md
│   ├── build-windows.md
│   └── deployment.md
├── installer/
│   ├── installer.nsi
│   └── installer.iss
├── .github/
│   └── workflows/
│       ├── build-linux.yml
│       └── build-windows.yml
├── database/
│   └── migrations/
│       ├── 001_initial_schema.sql
│       ├── 002_indexes_and_fts.sql
│       └── 003_seed_demo_data.sql
├── resources/
│   └── icons/
│       ├── app_icon.svg
│       └── diamond.svg
├── src/
│   ├── main.cpp
│   ├── app/
│   │   ├── AppPaths.h / AppPaths.cpp
│   │   ├── ApplicationController.h / ApplicationController.cpp
│   │   └── AppSettings.h / AppSettings.cpp
│   ├── database/
│   │   ├── DatabaseManager.h / DatabaseManager.cpp
│   │   └── DatabaseMigrations.h / DatabaseMigrations.cpp
│   ├── models/
│   │   ├── Diamond.h / Diamond.cpp
│   │   ├── Supplier.h / Supplier.cpp
│   │   ├── DiamondImage.h / DiamondImage.cpp
│   │   └── AuditLog.h / AuditLog.cpp
│   ├── models/qml/
│   │   ├── DiamondListModel.h / DiamondListModel.cpp
│   │   └── SupplierListModel.h / SupplierListModel.cpp
│   ├── repositories/
│   │   ├── DiamondRepository.h / DiamondRepository.cpp
│   │   ├── SupplierRepository.h / SupplierRepository.cpp
│   │   └── AuditRepository.h / AuditRepository.cpp
│   ├── services/
│   │   ├── InventoryService.h / InventoryService.cpp
│   │   ├── ImageService.h / ImageService.cpp
│   │   ├── BackupService.h / BackupService.cpp
│   │   ├── ExportService.h / ExportService.cpp
│   │   ├── ImportService.h / ImportService.cpp
│   │   ├── ReportService.h / ReportService.cpp
│   │   └── PrintService.h / PrintService.cpp
│   └── utils/
│       ├── Money.h / Money.cpp
│       ├── DateUtils.h / DateUtils.cpp
│       └── FileUtils.h / FileUtils.cpp
├── qml/
│   ├── Main.qml
│   ├── Theme.qml
│   ├── components/
│   │   ├── AppSidebar.qml
│   │   ├── SearchBar.qml
│   │   ├── StatCard.qml
│   │   ├── StatusBadge.qml
│   │   ├── DiamondTable.qml
│   │   ├── DiamondCard.qml
│   │   ├── DiamondImageGallery.qml
│   │   ├── FilterPanel.qml
│   │   ├── ConfirmDialog.qml
│   │   └── Toast.qml
│   └── pages/
│       ├── DashboardPage.qml
│       ├── InventoryPage.qml
│       ├── DiamondDetailsPage.qml
│       ├── AddEditDiamondModal.qml
│       ├── SuppliersPage.qml
│       ├── ReportsPage.qml
│       └── SettingsPage.qml
└── tests/
    ├── CMakeLists.txt
    ├── tst_database.cpp
    ├── tst_pricing.cpp
    ├── tst_validation.cpp
    └── tst_import_export.cpp
```

---

## Dependencies

- **C++ Compiler:** GCC 11+, Clang 13+, or MSVC 2019/2022 (C++17 standard)
- **CMake:** 3.20 or newer
- **Ninja:** 1.10 or newer
- **Qt 6 Framework (6.4+):**
  - `Qt6Core`
  - `Qt6Gui`
  - `Qt6Quick`
  - `Qt6QuickControls2`
  - `Qt6Qml`
  - `Qt6Sql` (with SQLite driver)
  - `Qt6PrintSupport`
  - `Qt6Svg`

---

## Arch Linux Build Instructions

### 1. Install Packages

```bash
sudo pacman -Syu --needed \
    base-devel \
    cmake \
    ninja \
    gcc \
    qt6-base \
    qt6-declarative \
    qt6-svg \
    qt6-tools
```

### 2. Configure & Build

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### 3. Run Application

```bash
./build/bin/DiamondInventory
```

### 4. Run Test Suite

```bash
ctest --test-dir build --output-on-failure
```

---

## Windows Build & Packaging

### Method A — GitHub Actions CI (Automated)

The `.github/workflows/build-windows.yml` workflow automatically builds, tests, deploys Qt runtime libraries with `windeployqt`, compiles the NSIS installer, and uploads `DiamondInventorySetup.exe` as a release artifact.

### Method B — Local MSVC Build

From the **x64 Native Tools Command Prompt for VS 2022**:

```cmd
set Qt6_DIR=C:\Qt\6.6.3\msvc2019_64
set PATH=%Qt6_DIR%\bin;%PATH%

cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="%Qt6_DIR%"
cmake --build build --config Release

windeployqt --qmldir qml --release --compiler-runtime build\bin\DiamondInventory.exe

makensis installer\installer.nsi
```

This generates `DiamondInventorySetup.exe`.

---

## Application Data Storage

All data is stored in the user's local application data directory:

- **Linux:** `~/.local/share/DiamondStore/Diamond Inventory/`
- **Windows:** `C:\Users\<User>\AppData\Local\DiamondStore\Diamond Inventory\`

Inside this directory:
- `database/inventory.db`: SQLite database file (WAL mode enabled)
- `images/diamonds/<id>/`: Managed original uploaded images
- `thumbnails/diamonds/<id>/`: Automatically generated 256x256 image thumbnails
- `backups/`: Automated and manual timestamped database snapshots
- `exports/`: Generated CSV exports and PDF specification sheets

---

## Running Automated Tests

All tests run via CTest:

```bash
ctest --test-dir build --output-on-failure
```

Test coverage includes:
1. `tst_database`: CRUD operations, unique reference enforcement, soft delete/archive, suppliers.
2. `tst_pricing`: Minor-unit currency math, MAD formatting, profit margin calculations.
3. `tst_validation`: Validation rules (required fields, negative weights/prices prevention, duplication).
4. `tst_import_export`: Full CSV export and import cycle with column header matching.

---

## Versioning & Release

This project adheres to Semantic Versioning (`MAJOR.MINOR.PATCH`):
- Version defined centrally in `CMakeLists.txt` (`project(DiamondInventory VERSION 1.0.0)`).
- Tagged releases trigger automated builds across Linux and Windows platforms.
