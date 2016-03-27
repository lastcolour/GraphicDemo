# Set output directories

if(DEFINED ENV{GD_BUILD_DIR})
  set(BUILD_OUT $ENV{GD_BUILD_DIR})
  message(STATUS "BUILD_OUT dir = ${BUILD_OUT}")
else()
  set(BUILD_OUT "${CMAKE_CURRENT_SOURCE_DIR}/../../_out/custom")
  message(STATUS "GD_BUILD_DIR is not set upped. Used: ${BUILD_OUT}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Runtimes output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Libraries output directory")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Libraries output directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)
                                           
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)
                                           
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)
