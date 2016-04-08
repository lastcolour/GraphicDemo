cmake_minimum_required(VERSION 2.8)

if(NOT GD_ROOT_DIR)
  set(GD_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
  set(GD_CONFIG_DIR "${GD_ROOT_DIR}/config/cmakes")
endif()

project(DemoApp)

include(${GD_CONFIG_DIR}/dirs.cmake)
include(${GD_CONFIG_DIR}/opengl.cmake)

set(TARGET_NAME "demo")

file(GLOB HEADERS "src/*.hpp") # TODO: Replace glob to file enumeration
file(GLOB SRC     "src/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/
                    ${GD_LIBS_ROOT_DIR}/core/include
                    ${GD_GLEW_INCLUDE_DIR}
                    ${OPEN_GL_INCLUDE_DIR})

add_executable(${TARGET_NAME} ${SRC} ${HEADERS})


# CoreLib link
if(NOT GD_DEMO_APP_INCLUDE_CORE_LIB)

  set(GD_LIB_CORE_LOOK_PATH "${GD_OUT_ROOT_DIR}/${GD_BUILD_PLATFORM}/${CMAKE_BUILD_TYPE}")

  find_library(CORE_LIB_PATH NAMES core libcore PATHS ${GD_LIB_CORE_LOOK_PATH} NO_DEFAULT_PATH)

  if(NOT CORE_LIB_PATH)
    message(SEND_ERROR "Can't found core lib at: ${GD_LIB_CORE_LOOK_PATH}")
  endif()

else()

  # Include CoreLib to AppDemo for easy development both targets
  add_subdirectory(${GD_LIBS_ROOT_DIR}/core "${CMAKE_BINARY_DIR}/corelib")
  set(CORE_LIB_PATH core)
  add_dependencies(${TARGET_NAME} ${CORE_LIB_PATH})

endif()

target_link_libraries(${TARGET_NAME} PRIVATE ${CORE_LIB_PATH})
target_link_libraries(${TARGET_NAME} PRIVATE ${OPEN_GL_LIB_PATH})

# Other target setups
if(MSVC)
  add_compile_options("-Wall")
endif()
message(STATUS "Target: ${TARGET_NAME}, compiled with flags: ${CMAKE_CXX_FLAGS}")
set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Apps/${PROJECT_NAME}")