cmake_minimum_required(VERSION 2.8)

project(demo)

include_directories(src)
include_directories(${CORE_LIB_INCLUDE_DIR})

file(GLOB HEADERS "src/*.hpp" )
file(GLOB SRC     "src/*.cpp" )

add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

add_dependencies(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} core)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Apps/${PROJECT_NAME}")