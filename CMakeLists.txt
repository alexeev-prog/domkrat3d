cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    domkrat3d
    VERSION 0.1.0
    DESCRIPTION "Lite 3D Game Engine in C++ Vulkan"
    HOMEPAGE_URL "https://github.com/alexeev-prog/domkrat3d"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

find_package(OpenGL REQUIRED)

# ---- Declare library ----

add_library(
    domkrat3d_domkrat3d
    source/domkrat3d.cpp
    source/graphics/core.cpp
    source/physics/core.cpp
    source/physics/kinematics.cpp
    source/mathematics/core.cpp
    source/mathematics/statistics.cpp
    source/informatics/core.cpp
)
target_link_libraries(
  domkrat3d_domkrat3d glfw ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS}
)
add_library(domkrat3d::domkrat3d ALIAS domkrat3d_domkrat3d)

include(GenerateExportHeader)
generate_export_header(
    domkrat3d_domkrat3d
    BASE_NAME domkrat3d
    EXPORT_FILE_NAME export/domkrat3d/domkrat3d_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(domkrat3d_domkrat3d PUBLIC DOMKRAT3D_STATIC_DEFINE)
endif()

set_target_properties(
    domkrat3d_domkrat3d PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME domkrat3d
    OUTPUT_NAME domkrat3d
)

target_include_directories(
    domkrat3d_domkrat3d ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    domkrat3d_domkrat3d SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(domkrat3d_domkrat3d PUBLIC cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT domkrat3d_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of domkrat3d"
  )
endif()

include(cmake/dev-mode.cmake)
