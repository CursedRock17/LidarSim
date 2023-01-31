#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "minizip::minizip" for configuration "Debug"
set_property(TARGET minizip::minizip APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(minizip::minizip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/libminizip.a"
  )

list(APPEND _cmake_import_check_targets minizip::minizip )
list(APPEND _cmake_import_check_files_for_minizip::minizip "${_IMPORT_PREFIX}/debug/lib/libminizip.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
