cmake_minimum_required(VERSION 2.8)

project(core)

file(GLOB HEADERS "include/core/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Libs/${PROJECT_NAME}")