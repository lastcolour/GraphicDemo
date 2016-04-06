cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
  set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")
endif()

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/opengl.cmake)

find_library(FREEGLUT_LIB_PATH NAMES freeglut glut PATHS ${GD_FREEGLUT_LINK_DIR} NO_DEFAULT_PATH)

if(NOT FREEGLUT_LIB_PATH)
  message(SEND_ERROR "Can't found freeglut lib at: ${GD_FREEGLUT_LINK_DIR}")
else()
  message(STATUS "Freeglut lib found in: ${GD_FREEGLUT_LINK_DIR}")
endif()

include_directories(${GD_FREEGLUT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Define variable: -DNDEBUG")
  add_definitions(-DNDEBUG)
  add_definitions(-DGD_WIN_DLL_BUILD)
endif()

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})
target_link_libraries(${TARGET_NAME} PRIVATE ${FREEGLUT_LIB_PATH})

# Other target setups
message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")