if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

  set(GD_BIN_TYPE_DIR "lin64")
  
else(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(CMAKE_SYSTEM_NAME STREQUAL "Windows")

    set(GD_BIN_TYPE_DIR "win32")

  else(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    
    message(STATUS "Unsuported platform: ${CMAKE_SYSTEM_NAME}")  
   
  endif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")


if(DEFINED ENV{GD_ROOT_PORJECT_DIR})
  
  set(GD_ROOT_PRJ_DIR $ENV{GD_ROOT_PORJECT_DIR})

  message(STATUS "GraphicsDemo root: ${GD_ROOT_PRJ_DIR}")
  set(GD_EXTERN_ROOT_DIR "${GD_ROOT_PRJ_DIR}/extern")
  
  # Variables for freeglut
  set(GD_FREEGLUT_ROOT_DIR    "${GD_EXTERN_ROOT_DIR}/libs/freeglut-3.0.0")
  set(GD_FREEGLUT_LIBS_DIR    "${GD_FREEGLUT_ROOT_DIR}/bin/${GD_BIN_TYPE_DIR}")
  set(GD_FREEGLUT_INCLUDE_DIR "${GD_FREEGLUT_ROOT_DIR}/include")

else()
  
  message(STATUS "Error: GD_ROOT_PORJECT_DIR not setuped")
   
endif()
