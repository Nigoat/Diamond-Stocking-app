# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/DiamondApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DiamondApp_autogen.dir/ParseCache.txt"
  "DiamondApp_autogen"
  "tests/CMakeFiles/tst_database_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/tst_database_autogen.dir/ParseCache.txt"
  "tests/CMakeFiles/tst_import_export_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/tst_import_export_autogen.dir/ParseCache.txt"
  "tests/CMakeFiles/tst_pricing_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/tst_pricing_autogen.dir/ParseCache.txt"
  "tests/CMakeFiles/tst_validation_autogen.dir/AutogenUsed.txt"
  "tests/CMakeFiles/tst_validation_autogen.dir/ParseCache.txt"
  "tests/tst_database_autogen"
  "tests/tst_import_export_autogen"
  "tests/tst_pricing_autogen"
  "tests/tst_validation_autogen"
  )
endif()
