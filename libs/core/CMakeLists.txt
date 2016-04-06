cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()
set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/opengl.cmake)

find_library(FREEGLUT_LIB_PATH NAMES freeglut glut PATHS ${GD_FREEGLUT_LINK_DIR} NO_DEFAULT_PATH)

if(NOT FREEGLUT_LIB_PATH)
  message(STATUS "Can't found freeglut lib at: ${GD_FREEGLUT_LINK_DIR}")
else()
  message(STATUS "Freeglut lib found is: ${GD_FREEGLUT_LINK_DIR}")
endif()

include_directories(${GD_FREEGLUT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # add check when debug lib link release freeglut
  add_definitions(-DNDEBUG)
  add_definitions(-DGD_WIN_DLL_BUILD)
endif()

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})
target_link_libraries(${TARGET_NAME} PRIVATE ${FREEGLUT_LIB_PATH})
  
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")