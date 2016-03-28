# Set output directories

if(DEFINED ENV{GD_BIN_FILES_LOC})

  set(BUILD_OUT $ENV{GD_BIN_DES_DIR})
  message(STATUS "Used output dir = ${BUILD_OUT}")

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Runtimes output directory")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Libraries output directory")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_OUT}" CACHE FILEPATH "Libraries output directory")

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)
                                           
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)
                                           
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${BUILD_OUT}/debug)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BUILD_OUT}/release)

else()

  message(STATUS "Used default output dir")

endif()
