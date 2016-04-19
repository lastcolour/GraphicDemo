cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
  set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")
endif()

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/opengl.cmake)

find_library(GLEW_LIB_PATH NAMES glew32 libGLEW glew GLEW PATHS ${GD_GLEW_LINK_DIR} NO_DEFAULT_PATH)
if(NOT GLEW_LIB_PATH)
  message(SEND_ERROR "Can't found GLEW lib at: ${GD_GLEW_LINK_DIR}")
else()
  message(STATUS "GLEW lib found in: ${GD_GLEW_LINK_DIR}")
endif()

find_library(SURFACE_LIB_PATH NAMES glfw glfw3 glfw3dll PATHS ${GD_GLFW_LINK_DIR} NO_DEFAULT_PATH)
if(NOT SURFACE_LIB_PATH)
  message(SEND_ERROR "Can't found surface service lib at: ${GD_GLFW_LINK_DIR}")
else()
  message(STATUS "Surface service lib found in: ${GD_GLFW_LINK_DIR}")
endif()

include_directories(${GD_GLFW_INCLUDE_DIR}
                    ${GD_GLEW_INCLUDE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB HEADERS "include/core/*.hpp"
                  "include/openGL/*.hpp")
file(GLOB SRC     "src/*.cpp" )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_definitions(-DGD_WIN_DLL_BUILD)
endif()

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${TARGET_NAME} PUBLIC ${GLEW_LIB_PATH}) # Show opengl interface
target_link_libraries(${TARGET_NAME} PRIVATE ${SURFACE_LIB_PATH})

# Other target setups
message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")
