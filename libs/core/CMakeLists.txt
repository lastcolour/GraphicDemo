cmake_minimum_required(VERSION 2.8)

project(corelib)

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/core/)

add_library(${PROJECT_NAME} ${SRC} ${HEADERS})