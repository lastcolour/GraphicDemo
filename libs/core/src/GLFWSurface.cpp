// author: Oleksii Zhogan

#include <openGL/openGL.hpp>

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>


#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <assert.h>


bool GLFWSurface::GLFW_LIB_INITED = false;
bool GLFWSurface::GLEW_LIB_INITED = false;


GLFWSurface::GLFWSurface() :
    Surface(),
    windowHandler(nullptr) {

    if(!GLFW_LIB_INITED) {
        GLFW_LIB_INITED = glfwInit() == GL_TRUE;
        assert(GLFW_LIB_INITED && "GLFW Lib should be initialized");
        std::atexit([](){
            glfwTerminate();
        });
    }
}

GLFWSurface::~GLFWSurface() {
    if(!windowHandler) {
        glfwDestroyWindow(windowHandler);
    }
}

void GLFWSurface::setTitle(const char* title) {
    this->title = title;
}

void GLFWSurface::setGeometry(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void GLFWSurface::setResizeable(bool flag) {
    resizeable = flag;
}

void GLFWSurface::setOpenGL(unsigned int major, unsigned int minor) {
    openGLMajor = static_cast<int>(major);
    openGLMinor = static_cast<int>(minor);
}

void GLFWSurface::setCoreProfile(bool flag) {
    corePorfile = flag;
}

void GLFWSurface::sendInputEvents() {
    glfwPollEvents();
}

bool GLFWSurface::isOpen() {
    if(windowHandler) {
        if(glfwWindowShouldClose(windowHandler) != GL_TRUE) {
            return true;
        }
        windowHandler = nullptr;
    }
    return false;
}

void GLFWSurface::swapBuffers() {
    if(windowHandler) {
        glfwSwapBuffers(windowHandler);
    }
}

void GLFWSurface::close() {
    if(windowHandler) {
        glfwSetWindowShouldClose(windowHandler, GL_TRUE);
    }
}

bool GLFWSurface::initGLEW() {
    if(!GLEW_LIB_INITED) {
        glewExperimental = GL_TRUE;
        GLenum errCode = GL_NO_ERROR;
        if((errCode = glewInit()) != GLEW_OK) {
            const GLubyte* errStr = glewGetErrorString(errCode);
            std::cerr << "[GLEW] GLEW init error: " << reinterpret_cast<const char*>(errStr) << std::endl; 
            return false;
        }
        errCode = GL_NO_ERROR;
        if((errCode = glGetError()) != GL_NO_ERROR) {
            std::cerr << "[GLEW] OpenGL error: " << reinterpret_cast<const char*>(gluErrorString(errCode)) << std::endl; 
            //return false;
        }
        GLEW_LIB_INITED = true;
    }
    return true;
}

bool GLFWSurface::show() {
    if(windowHandler) {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGLMinor);
    glfwWindowHint(GLFW_RESIZABLE, resizeable);
    if (corePorfile) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

#ifdef GD_CORE_LIB_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif /* GD_CORE_LIB_DEBUG */

    windowHandler = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!windowHandler) {
        return false;
    }
    glfwMakeContextCurrent(windowHandler);
    if(!initGLEW()) {
        glfwDestroyWindow(windowHandler);
        return false;
    }
    Application::getInstance()->onResizeEvent(width, height);
    return true;
}
