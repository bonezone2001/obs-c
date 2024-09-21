cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  obsc
  VERSION 0.1.0
  DESCRIPTION "Leverage the power obs's graphics dll for capturing game frames"
  LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(obsc_obsc
  # Obsc
  src/obsc.cpp
  src/utils.cpp
  src/event.cpp
  src/pipe.cpp
  src/mutex.cpp
)
add_library(obsc::obsc ALIAS obsc_obsc)

include(GenerateExportHeader)
generate_export_header(
  obsc_obsc
  BASE_NAME obsc
  EXPORT_FILE_NAME export/obsc/obsc_export.hpp
  CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(obsc_obsc PUBLIC obsc_STATIC_DEFINE)
endif()

set_target_properties(
  obsc_obsc PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  EXPORT_NAME obsc
  OUTPUT_NAME obsc
)

target_include_directories(
  obsc_obsc ${warning_guard}
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  obsc_obsc SYSTEM
  PUBLIC
  "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(obsc_obsc PUBLIC cxx_std_20)

# Link dependencies
find_package(fmt REQUIRED)
target_link_libraries(obsc_obsc PRIVATE fmt::fmt)

# Prevent windows.h from including winsock.h
add_definitions(-D_WINSOCKAPI_)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT obsc_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of obsc"
  )
endif()

include(cmake/dev-mode.cmake)
