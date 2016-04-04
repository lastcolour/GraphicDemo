cmake_minimum_required(VERSION 2.8)

if(not ${GD_CONFIG_DIR})
  set(GD_CONFIG_DIR "../../config/cmakes")
endif()

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/opengl.cmake)

# Add freeglut (only shared link)
find_library(FREEGLUT_LIB_LOC NAMES freeglut glut PATHS ${GD_FREEGLUT_LIBS_DIR} NO_DEFAULT_PATH)

if(NOT FREEGLUT_LIB_LOC)
  message(STATUS "Can't found freeglut lib at: ${GD_FREEGLUT_LIBS_DIR}")
else()
  message(STATUS "Freeglut lib found is: ${FREEGLUT_LIB_LOC}")
endif()

include_directories(${GD_FREEGLUT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # Add check when debug lib link release freeglut
  add_definitions(-DNDEBUG)
endif()

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})

target_link_libraries(${TARGET_NAME} PRIVATE ${FREEGLUT_LIB_LOC})
  
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")
