if(NOT GD_DIRS_CMAKE_INCLUDED)

  # Require dirs.cmake included first
  message(SEND_ERROR "Please include cmake config file first: dirs.cmake")

endif()

# Link directoriesa are consistent with config files at "projects" dirs

set(GD_FREEGLUT_INCLUDE_DIR "${GD_EXTERN_ROOT_DIR}/libs/freeglut-3.0.0/include")
set(GD_FREEGLUT_LINK_DIR "${GD_OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")

set(GD_GLEW_INCLUDE_DIR "${GD_EXTERN_ROOT_DIR}/libs/glew-1.13.0/include")
set(GD_GLEW_LINK_DIR "${GD_OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")

find_package(OpenGL REQUIRED)
set(OPEN_GL_LIB_PATH ${OPENGL_gl_LIBRARY})
