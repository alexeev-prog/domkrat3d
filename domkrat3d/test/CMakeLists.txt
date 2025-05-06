cmake_minimum_required(VERSION 3.14)

project(domkrat3dTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(domkrat3d REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(domkrat3d_test source/domkrat3d_test.cpp)
target_link_libraries(domkrat3d_test PRIVATE domkrat3d::domkrat3d)
target_compile_features(domkrat3d_test PRIVATE cxx_std_17)

add_test(NAME domkrat3d_test COMMAND domkrat3d_test)

# ---- End-of-file commands ----

add_folders(Test)
