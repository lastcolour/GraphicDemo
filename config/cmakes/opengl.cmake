if(NOT GD_DIRS_CMAKE_INCLUDED)

  # Require dirs.cmake included first
  message(SEND_ERROR "Please include cmake config file first: dirs.cmake")

endif()

set(GD_FREEGLUT_INCLUDE_DIR "${GD_EXTERN_ROOT_DIR}/libs/freeglut-3.0.0/include")
set(GD_FREEGLUT_LINK_DIR "${GD_OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")