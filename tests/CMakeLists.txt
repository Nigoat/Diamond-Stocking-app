find_package(Qt6 REQUIRED COMPONENTS Test Sql Gui Quick Qml PrintSupport Svg)

set(TEST_COMMON_SRCS
    ../src/utils/Money.h
    ../src/utils/Money.cpp
    ../src/utils/DateUtils.h
    ../src/utils/DateUtils.cpp
    ../src/utils/FileUtils.h
    ../src/utils/FileUtils.cpp
    ../src/app/AppPaths.h
    ../src/app/AppPaths.cpp
    ../src/app/AppSettings.h
    ../src/app/AppSettings.cpp
    ../src/models/Diamond.h
    ../src/models/Diamond.cpp
    ../src/models/Supplier.h
    ../src/models/Supplier.cpp
    ../src/models/DiamondImage.h
    ../src/models/DiamondImage.cpp
    ../src/models/AuditLog.h
    ../src/models/AuditLog.cpp
    ../src/database/DatabaseMigrations.h
    ../src/database/DatabaseMigrations.cpp
    ../src/database/DatabaseManager.h
    ../src/database/DatabaseManager.cpp
    ../src/repositories/SupplierRepository.h
    ../src/repositories/SupplierRepository.cpp
    ../src/repositories/AuditRepository.h
    ../src/repositories/AuditRepository.cpp
    ../src/repositories/DiamondRepository.h
    ../src/repositories/DiamondRepository.cpp
    ../src/services/ImageService.h
    ../src/services/ImageService.cpp
    ../src/services/BackupService.h
    ../src/services/BackupService.cpp
    ../src/services/ExportService.h
    ../src/services/ExportService.cpp
    ../src/services/ImportService.h
    ../src/services/ImportService.cpp
    ../src/services/ReportService.h
    ../src/services/ReportService.cpp
    ../src/services/PrintService.h
    ../src/services/PrintService.cpp
    ../src/services/InventoryService.h
    ../src/services/InventoryService.cpp
)

set(TEST_INCLUDES
    ../src/app
    ../src/database
    ../src/models
    ../src/repositories
    ../src/services
    ../src/utils
)

add_executable(tst_database tst_database.cpp ${TEST_COMMON_SRCS})
target_include_directories(tst_database PRIVATE ${TEST_INCLUDES})
target_link_libraries(tst_database PRIVATE Qt6::Test Qt6::Sql Qt6::Gui Qt6::PrintSupport Qt6::Svg)
add_test(NAME tst_database COMMAND tst_database)

add_executable(tst_pricing tst_pricing.cpp ${TEST_COMMON_SRCS})
target_include_directories(tst_pricing PRIVATE ${TEST_INCLUDES})
target_link_libraries(tst_pricing PRIVATE Qt6::Test Qt6::Sql Qt6::Gui Qt6::PrintSupport Qt6::Svg)
add_test(NAME tst_pricing COMMAND tst_pricing)

add_executable(tst_validation tst_validation.cpp ${TEST_COMMON_SRCS})
target_include_directories(tst_validation PRIVATE ${TEST_INCLUDES})
target_link_libraries(tst_validation PRIVATE Qt6::Test Qt6::Sql Qt6::Gui Qt6::PrintSupport Qt6::Svg)
add_test(NAME tst_validation COMMAND tst_validation)

add_executable(tst_import_export tst_import_export.cpp ${TEST_COMMON_SRCS})
target_include_directories(tst_import_export PRIVATE ${TEST_INCLUDES})
target_link_libraries(tst_import_export PRIVATE Qt6::Test Qt6::Sql Qt6::Gui Qt6::PrintSupport Qt6::Svg)
add_test(NAME tst_import_export COMMAND tst_import_export)
