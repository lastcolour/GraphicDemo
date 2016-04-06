cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()
set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")

project(DemoApp)

include(${GD_CONFIG_DIR}/dirs.cmake)

set(TARGET_NAME "demo")

file(GLOB HEADERS "src/*.hpp")
file(GLOB SRC     "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/
                    ${GD_LIBS_ROOT_DIR}/core/include)

add_executable(${TARGET_NAME} ${SRC} ${HEADERS})

if(NOT GD_DEMO_APP_INCLUDE_CORE_LIB)

  set(GD_LIB_CORE_FIND_PATH "${GD_OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")
  
  find_library(CORE_LIB_PATH NAMES core libcore PATHS ${GD_LIB_CORE_FIND_PATH} NO_DEFAULT_PATH)
  if(NOT CORE_LIB_PATH)
    message(STATUS "Can't found core lib at: ${GD_LIB_CORE_FIND_PATH}")
  endif()
  
else()
  
  add_subdirectory(${GD_LIBS_ROOT_DIR}/core "${CMAKE_BINARY_DIR}/corelib")
  set(CORE_LIB_PATH core)
  add_dependencies(${TARGET_NAME} ${CORE_LIB_PATH})
  
endif()

message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")

target_link_libraries(${TARGET_NAME} PRIVATE ${CORE_LIB_PATH})

set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Apps/${PROJECT_NAME}")