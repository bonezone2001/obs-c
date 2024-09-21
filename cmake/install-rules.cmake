if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/obsc-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package obsc)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT obsc_Development
)

install(
    TARGETS obsc_obsc
    EXPORT obscTargets
    RUNTIME #
    COMPONENT obsc_Runtime
    LIBRARY #
    COMPONENT obsc_Runtime
    NAMELINK_COMPONENT obsc_Development
    ARCHIVE #
    COMPONENT obsc_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    obsc_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE obsc_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(obsc_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${obsc_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT obsc_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${obsc_INSTALL_CMAKEDIR}"
    COMPONENT obsc_Development
)

install(
    EXPORT obscTargets
    NAMESPACE obsc::
    DESTINATION "${obsc_INSTALL_CMAKEDIR}"
    COMPONENT obsc_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
