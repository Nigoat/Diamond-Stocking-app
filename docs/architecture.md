# Architecture Overview

## Technology Stack

- **Language:** C++17
- **UI Framework:** Qt 6 (Qt Quick, QML, Qt Quick Controls 2)
- **Database:** SQLite 3 via Qt SQL
- **Build System:** Modern CMake (3.20+) with Ninja
- **Currency System:** Minor-unit integer cents for Moroccan Dirham (MAD) to prevent floating-point drift

## Architectural Layers

```text
+-------------------------------------------------------------+
|                      QML User Interface                     |
|  - Theme, Navigation, Pages (Dashboard, Inventory, etc.)    |
|  - Components (Table, Cards, ImageGallery, FilterPanel)     |
+-------------------------------------------------------------+
                              | (Q_INVOKABLE, Q_PROPERTY, Signals)
+-------------------------------------------------------------+
|                    Application Controller                   |
|  - ApplicationController (Single coordinator to QML)        |
|  - DiamondListModel (QAbstractListModel with filtering)     |
|  - SupplierListModel (QAbstractListModel)                   |
|  - AppSettings (QSettings + SQLite key-value store)         |
+-------------------------------------------------------------+
                              |
+-------------------------------------------------------------+
|                       Services Layer                        |
|  - InventoryService: CRUD, duplicate, bulk status/price     |
|  - ImageService: storage management, 256x256 thumbnails     |
|  - BackupService: automated timestamped snapshots, restore  |
|  - ExportService: UTF-8 CSV, tabular PDF reports            |
|  - ImportService: CSV parsing, validation, batch insert     |
|  - ReportService: aggregated analytics and breakdowns       |
|  - PrintService: Diamond specification sheet PDF rendering  |
+-------------------------------------------------------------+
                              |
+-------------------------------------------------------------+
|                     Repositories Layer                      |
|  - DiamondRepository, SupplierRepository, AuditRepository   |
+-------------------------------------------------------------+
                              |
+-------------------------------------------------------------+
|                   Database & Utility Layer                  |
|  - DatabaseManager: WAL mode, foreign keys, transactions    |
|  - DatabaseMigrations: versioned SQL schema migrations      |
|  - Money: fixed-precision monetary math and MAD formatting  |
|  - AppPaths: platform-specific standard storage paths       |
+-------------------------------------------------------------+
```

## Directory Structure

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
├── resources/
│   └── icons/
├── src/
│   ├── main.cpp
│   ├── app/
│   ├── database/
│   ├── models/
│   │   └── qml/
│   ├── repositories/
│   ├── services/
│   └── utils/
├── qml/
│   ├── Main.qml
│   ├── Theme.qml
│   ├── components/
│   └── pages/
└── tests/
```
