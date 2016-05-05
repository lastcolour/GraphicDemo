// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __OPEN_GL_HPP__
#define __OPEN_GL_HPP__

#include <core/DEFS.hpp>
#include <GL/glew.h>

#define OPENGL_STR_BUF_SIZE 512

#ifndef GD_WIN_DLL_BUILD
    #include <GL/glut.h>
#endif


#ifdef GD_CORE_LIB_DEBUG
    #include <openGL/GLutils.hpp>

    #define CHECK_OPENGL_STATUS( PLACE_NAME ) \
    printGLerror( PLACE_NAME );
#else
    #define GD_CORE_LIB_DEBUG ( PLACE_NAME ) 
#endif /* GD_CORE_LIB_DEBUG */


#endif /* __OPEN_GL_HPP__ */
