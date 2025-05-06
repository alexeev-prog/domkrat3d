if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/domkrat3d-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package domkrat3d)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT domkrat3d_Development
)

install(
    TARGETS domkrat3d_domkrat3d
    EXPORT domkrat3dTargets
    RUNTIME #
    COMPONENT domkrat3d_Runtime
    LIBRARY #
    COMPONENT domkrat3d_Runtime
    NAMELINK_COMPONENT domkrat3d_Development
    ARCHIVE #
    COMPONENT domkrat3d_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    domkrat3d_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE domkrat3d_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(domkrat3d_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${domkrat3d_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT domkrat3d_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${domkrat3d_INSTALL_CMAKEDIR}"
    COMPONENT domkrat3d_Development
)

install(
    EXPORT domkrat3dTargets
    NAMESPACE domkrat3d::
    DESTINATION "${domkrat3d_INSTALL_CMAKEDIR}"
    COMPONENT domkrat3d_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
