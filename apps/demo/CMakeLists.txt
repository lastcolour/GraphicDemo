cmake_minimum_required(VERSION 2.8)

project(demo)

file(GLOB HEADERS "src/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

set(CORELIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}../../libs/core/")

include_directories(${CORE_LIB_ROOT}/include)
include_directories(${CORELIB_ROOT}/include)

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

target_link_libraries(${PROJECT_NAME} STATIC core)