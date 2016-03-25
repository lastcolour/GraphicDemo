cmake_minimum_required(VERSION 2.8)

project(Apps)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(LIBS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../libs")
set(EXTERNALS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../externals")

# Internal libs
add_subdirectory(${LIBS_ROOT}/core "${CMAKE_CURRENT_BINARY_DIR}/libs/core")
set(CORE_LIB_INCLUDE_DIR "${LIBS_ROOT}/core/include")

# Applications
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/demo "${CMAKE_CURRENT_BINARY_DIR}/demo")

