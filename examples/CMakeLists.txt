cmake_minimum_required(VERSION 3.14)

project(domkrat3dTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(domkrat3d REQUIRED)
  # enable_testing()
endif()

# ---- Examples ----

add_executable(domkrat3d_example_full full.cpp)
target_link_libraries(domkrat3d_example_full PRIVATE domkrat3d::domkrat3d)
target_compile_features(domkrat3d_example_full PRIVATE cxx_std_17)

add_test(NAME domkrat3d_example_full COMMAND domkrat3d_example_full)

# ---- End-of-file commands ----

add_folders(Examples)
