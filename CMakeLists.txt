cmake_minimum_required(VERSION 3.20)

project(DiamondInventory VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    QuickControls2
    Qml
    Sql
    PrintSupport
    Svg
)

qt_standard_project_setup()

set(SRC_FILES
    src/main.cpp
    src/utils/Money.h
    src/utils/Money.cpp
    src/utils/DateUtils.h
    src/utils/DateUtils.cpp
    src/utils/FileUtils.h
    src/utils/FileUtils.cpp
    src/app/AppPaths.h
    src/app/AppPaths.cpp
    src/app/AppSettings.h
    src/app/AppSettings.cpp
    src/app/ApplicationController.h
    src/app/ApplicationController.cpp
    src/models/Diamond.h
    src/models/Diamond.cpp
    src/models/Supplier.h
    src/models/Supplier.cpp
    src/models/DiamondImage.h
    src/models/DiamondImage.cpp
    src/models/AuditLog.h
    src/models/AuditLog.cpp
    src/database/DatabaseMigrations.h
    src/database/DatabaseMigrations.cpp
    src/database/DatabaseManager.h
    src/database/DatabaseManager.cpp
    src/repositories/SupplierRepository.h
    src/repositories/SupplierRepository.cpp
    src/repositories/AuditRepository.h
    src/repositories/AuditRepository.cpp
    src/repositories/DiamondRepository.h
    src/repositories/DiamondRepository.cpp
    src/services/ImageService.h
    src/services/ImageService.cpp
    src/services/BackupService.h
    src/services/BackupService.cpp
    src/services/ExportService.h
    src/services/ExportService.cpp
    src/services/ImportService.h
    src/services/ImportService.cpp
    src/services/ReportService.h
    src/services/ReportService.cpp
    src/services/PrintService.h
    src/services/PrintService.cpp
    src/services/InventoryService.h
    src/services/InventoryService.cpp
    src/models/qml/DiamondListModel.h
    src/models/qml/DiamondListModel.cpp
    src/models/qml/SupplierListModel.h
    src/models/qml/SupplierListModel.cpp
)

qt_add_executable(DiamondApp
    ${SRC_FILES}
    resources/icons/app_icon.svg
    resources/icons/diamond.svg
)

set_target_properties(DiamondApp PROPERTIES
    OUTPUT_NAME "DiamondInventory"
)

target_include_directories(DiamondApp PRIVATE
    src/app
    src/database
    src/models
    src/models/qml
    src/repositories
    src/services
    src/utils
)

qt_add_qml_module(DiamondApp
    URI DiamondInventory
    VERSION 1.0
    RESOURCE_PREFIX /
    QML_FILES
        qml/Main.qml
        qml/Theme.qml
        qml/components/StatusBadge.qml
        qml/components/Toast.qml
        qml/components/StatCard.qml
        qml/components/SearchBar.qml
        qml/components/FilterPanel.qml
        qml/components/DiamondCard.qml
        qml/components/DiamondTable.qml
        qml/components/DiamondImageGallery.qml
        qml/components/ConfirmDialog.qml
        qml/components/AppSidebar.qml
        qml/pages/DashboardPage.qml
        qml/pages/InventoryPage.qml
        qml/pages/AddEditDiamondModal.qml
        qml/pages/DiamondDetailsPage.qml
        qml/pages/SuppliersPage.qml
        qml/pages/ReportsPage.qml
        qml/pages/SettingsPage.qml
    RESOURCES
        resources/icons/app_icon.svg
        resources/icons/diamond.svg
)

set_source_files_properties(qml/Theme.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

target_link_libraries(DiamondApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Qml
    Qt6::Sql
    Qt6::PrintSupport
    Qt6::Svg
)

if(WIN32)
    set_target_properties(DiamondApp PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    if(COMMAND qt_generate_deploy_qml_app_script)
        qt_generate_deploy_qml_app_script(
            TARGET DiamondApp
            OUTPUT_SCRIPT deploy_script
            DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORMS
        )
        install(SCRIPT ${deploy_script})
    endif()
endif()

enable_testing()
add_subdirectory(tests)
