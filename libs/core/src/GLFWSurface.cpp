// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>

#include <openGL/openGL.hpp>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <assert.h>


bool GLFWSurface::GLFW_LIB_INITED = false;


GLFWSurface::GLFWSurface(Application* app) :
    Surface(app),
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

void GLFWSurface::setTitle(const std::string& title) {
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
    windowHandler = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!windowHandler) {
        return false;
    }
    glfwMakeContextCurrent(windowHandler);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        return false;
    }
    getApp()->onResizeEvent(width, height);
    return true;
}
