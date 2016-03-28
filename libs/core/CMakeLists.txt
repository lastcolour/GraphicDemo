cmake_minimum_required(VERSION 2.8)

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/opengl.cmake)

# Add freeglut
message(STATUS "Freeglut search path: ${GD_FREEGLUT_LIBS_DIR}")
find_library(FREEGLUT_LIB_LOC NAMES libglut glut PATHS ${GD_FREEGLUT_LIBS_DIR} NO_DEFAULT_PATH)
include_directories(${GD_FREEGLUT_INCLUDE_DIR})

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})

target_link_libraries(${TARGET_NAME} PRIVATE ${FREEGLUT_LIB_LOC})

set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")
