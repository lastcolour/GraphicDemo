cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
  set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")
endif()

option(GD_CORE_LIB_DEBUG ON)

project(core)

set(TARGET_NAME "core")

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/opengl.cmake)

find_library(GLEW_LIB_PATH NAMES glew32 libGLEW glew GLEW PATHS ${GD_GLEW_LINK_DIR} NO_DEFAULT_PATH)
if(NOT GLEW_LIB_PATH)
  message(SEND_ERROR "Can't found GLEW lib in: ${GD_GLEW_LINK_DIR}")
else()
  message(STATUS "GLEW lib found in: ${GD_GLEW_LINK_DIR}")
endif()

find_library(SURFACE_LIB_PATH NAMES glfw glfw3 glfw3dll PATHS ${GD_GLFW_LINK_DIR} NO_DEFAULT_PATH)
if(NOT SURFACE_LIB_PATH)
  message(SEND_ERROR "Can't found surface service lib in: ${GD_GLFW_LINK_DIR}")
else()
  message(STATUS "Surface service lib found in: ${GD_GLFW_LINK_DIR}")
endif()

include_directories(${GD_GLFW_INCLUDE_DIR}
                    ${GD_GLEW_INCLUDE_DIR}
                    ${GD_STB_IMAGE_INCLUDE_DIR}
                    ${GD_GLM_INCLUDE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB HEADERS "include/core/*.hpp"
                  "include/openGL/*.hpp"
                  "include/graphics/*.hpp")
file(GLOB SRC     "src/*.cpp" )

if(GD_CORE_LIB_DEBUG)
  add_definitions(-DGD_CORE_LIB_DEBUG)
endif()

add_library(${TARGET_NAME} SHARED ${SRC} ${HEADERS})

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${TARGET_NAME} PRIVATE ${SURFACE_LIB_PATH})
target_link_libraries(${TARGET_NAME} PRIVATE  ${GLEW_LIB_PATH})
target_link_libraries(${TARGET_NAME} PUBLIC  ${OPEN_GL_LIB_PATH}) # Show opengl interface

# Other target setups
message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")