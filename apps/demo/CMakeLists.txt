cmake_minimum_required(VERSION 2.8)

set(GD_ROOT_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/../../")
set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")
set(LIBS_ROOT_DIR "${GD_ROOT_DIR}/libs")

project(DemoApp)

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/projects.cmake)

set(TARGET_NAME "demo")

file(GLOB HEADERS "src/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/
                    ${LIBS_ROOT_DIR}/core/include)

message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")
                    
add_executable(${TARGET_NAME} ${SRC} ${HEADERS})
target_link_libraries(${TARGET_NAME} core)

set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Apps/${PROJECT_NAME}")