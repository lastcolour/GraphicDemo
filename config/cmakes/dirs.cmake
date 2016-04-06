# Set output directories

set(GD_DIRS_CMAKE_INCLUDED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(GD_BUILD_PLATFORM "Windows")
else()
  # TODO: Verify that current platform is windwos
  set(GD_BUILD_PLATFORM "Linux")
endif()

if(NOT GD_ROOT_DIR AND NOT ENV{GD_OUT_DIR})
  message(SEND_ERROR "GraphicDemo root dir not defined (var = GD_OUT_DIR)")
endif()

# Set global property of generated projects
if (MSVC)
  # Affect only for VS
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

set(GD_LIBS_ROOT_DIR "${GD_ROOT_DIR}/libs")
set(GD_EXTERN_ROOT_DIR "${GD_ROOT_DIR}/extern")

# Set up output path
set(GD_OUT_DIR_NAME "_out")
set(GD_OUT_ROOT_DIR "${GD_ROOT_DIR}/${GD_OUT_DIR_NAME}/${GD_BUILD_PLATFORM}")

# TODO: Remake for alternative path
# set(GD_OUT_ROOT_DIR "${GD_ROOT_DIR}/${GD_OUT_DIR_NAME}/${GD_BUILD_PLATFORM}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${GD_OUT_ROOT_DIR}" CACHE FILEPATH "Runtimes output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${GD_OUT_ROOT_DIR}" CACHE FILEPATH "Libraries output directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${GD_OUT_ROOT_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${GD_OUT_ROOT_DIR}/Release)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${GD_OUT_ROOT_DIR}/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${GD_OUT_ROOT_DIR}/Release)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${GD_OUT_ROOT_DIR}/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${GD_OUT_ROOT_DIR}/Release)