cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project (Physics)

set (LIB_NAME "physics")

file (GLOB SRC_FILES    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file (GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${LIB_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 11)
