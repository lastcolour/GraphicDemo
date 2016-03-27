cmake_minimum_required(VERSION 2.8)

project(core)

set(TARGET_NAME "core")

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${TARGET_NAME} STATIC ${SRC} ${HEADERS})

set_property(TARGET ${TARGET_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")
