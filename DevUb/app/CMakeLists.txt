cmake_minimum_required (VERSION 3.1 FATAL_ERROR)

project (DevUBIApp)

#==------------- Build options -------------==
option (X64_BUILD           "x64 build"           ON)

if (X64_BUILD)
  set (PLATFORM "x64")
else (X64_BUILD)
  set (PLATFORM "x32")
endif (X64_BUILD)

#==------------- Setup libs -------------==

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Setup build paths
set (ROOT_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/..")
set (OUT_ROOT_DIR "${ROOT_DIR}/_out")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUT_ROOT_DIR}" CACHE FILEPATH "Runtimes output directory")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_ROOT_DIR}" CACHE FILEPATH "Libraries output directory")

set (PHYSICS_LIB "physics")
set (PHYSICS_LIB_DIR         "${ROOT_DIR}/${PHYSICS_LIB}")
set (PHYSICS_LIB_INCLUDE_DIR "${PHYSICS_LIB_DIR}/include")

set (GLEW_DIR         "${ROOT_DIR}/extern/glew")
set (GLEW_INCLUDE_DIR "${GLEW_DIR}/include")
set (GLEW_LINK_DIR    "${GLEW_DIR}/bins/${PLATFORM}")

set (GLFW_DIR         "${ROOT_DIR}/extern/glfw")
set (GLFW_INCLUDE_DIR "${GLFW_DIR}/include")
set (GLFW_LINK_DIR    "${GLFW_DIR}/bins/${PLATFORM}")

#==------------- Project setting -------------==
# Results app name
set (APP_NAME "devUBI")

# Project sources
set (SRC_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set (SHADER_DIR_NAME "shaders")

file (GLOB SRC_FILES    "${SRC_DIR}/*.cpp")
file (GLOB HEADER_FILES "${SRC_DIR}/*.hpp")
file (GLOB SHADER_FILES "${SHADER_DIR}/*.glsl")

# OpenGL, GLEW and GLFW dependiceis (dynamic linking)
find_package (OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
  message(SEND_ERROR "Can't find openGL on this machine")
endif ()

find_library (GLEW_LIB NAMES glew32 libGLEW glew GLEW PATHS ${GLEW_LINK_DIR} NO_DEFAULT_PATH)
file(GLOB GLFW_DLLS "${GLEW_LINK_DIR}/*.*")
file(COPY ${GLFW_DLLS} DESTINATION "${OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")

if(NOT GLEW_LIB)
  message(SEND_ERROR "Can't found GLEW lib in: ${GLEW_LINK_DIR}")
endif()

find_library(GLFW_LIB NAMES glfw glfw3 glfw3dll PATHS ${GLFW_LINK_DIR} NO_DEFAULT_PATH)
file(GLOB GLEW_DLLS "${GLFW_LINK_DIR}/*.*")
file(COPY ${GLEW_DLLS} DESTINATION "${OUT_ROOT_DIR}/${CMAKE_BUILD_TYPE}")
if(NOT GLFW_LIB)
  message(SEND_ERROR "Can't found GLFW lib in: ${GLFW_LINK_DIR}")
endif()

# Include directories
include_directories (${SRC_DIR}
                     ${GLEW_INCLUDE_DIR}
                     ${GLFW_INCLUDE_DIR}
                     ${OPENGL_INCLUDE_DIR}
                     ${PHYSICS_LIB_INCLUDE_DIR})

#==------------- Build executable -------------==                     
add_executable(${APP_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 11)

# Add physics lib to this project
add_subdirectory (${PHYSICS_LIB_DIR} "${CMAKE_BINARY_DIR}/${PHYSICS_LIB}")
add_dependencies (${APP_NAME} ${PHYSICS_LIB})

# Link with libraies
target_link_libraries(${APP_NAME} PRIVATE ${GLEW_LIB})
target_link_libraries(${APP_NAME} PRIVATE ${GLFW_LIB})
target_link_libraries(${APP_NAME} PRIVATE ${PHYSICS_LIB})
target_link_libraries(${APP_NAME} PRIVATE ${OPENGL_LIBRARIES})

# Link pthread lib on Linux
if (CMAKE_COMPILER_IS_GNUCXX)
  find_package(Threads REQUIRED)
  target_link_libraries(${APP_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()


# Copy shaders
message(STATUS "Copy shaders in: ${SHADER_DIR}")
add_custom_command (TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_DIR}
        $<TARGET_FILE_DIR:${APP_NAME}>/"${SHADER_DIR_NAME}")	
