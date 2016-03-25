cmake_minimum_required(VERSION 2.8)

project(Apps)

# Projects global variables
set(GRAPHIC_DEMO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(CMAKE_CONFIG_ROOT "${GRAPHIC_DEMO_ROOT}/config/cmakes")
set(LIBS_ROOT         "${GRAPHIC_DEMO_ROOT}/libs")
set(EXTERNALS_ROOT    "${GRAPHIC_DEMO_ROOT}/externals")

# Add global config
include(${CMAKE_CONFIG_ROOT}/dirs.cmake)
include(${CMAKE_CONFIG_ROOT}/projects.cmake)

# Internal libs
add_subdirectory(${LIBS_ROOT}/core "${CMAKE_CURRENT_BINARY_DIR}/libs/core")
set(CORE_LIB_INCLUDE_DIR "${LIBS_ROOT}/core/include")

# Applications
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/demo "${CMAKE_CURRENT_BINARY_DIR}/demo")