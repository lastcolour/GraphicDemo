// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>

#include <GLFW/glfw3.h>
#include <assert.h>


// Static methods implementation

bool GLFWSurface::GLFW_LIB_INITED = false;

bool GLFWSurface::initialize() {
    GLFW_LIB_INITED = GL_TRUE == glfwInit();
    return GLFW_LIB_INITED;
}

bool GLFWSurface::deinitialize() {
    if (GLFW_LIB_INITED) {
        glfwTerminate();
    }
    return true;
};

// Class implementation

GLFWSurface::GLFWSurface(Application* app) :
    Surface(app), dataHandler(new GLFWDataHandler()) {
}


GLFWSurface::~GLFWSurface() {
}

void GLFWSurface::setTitle(const std::string& title) {
    dataHandler->setTitle(title);
}

void GLFWSurface::setBufferMode(SurfaceBufferMode mode) {
    dataHandler->setBufferMode(mode);
}

void GLFWSurface::setColorMode(SurfaceColorMode mode) {
    dataHandler->setColorMode(mode);
}

void GLFWSurface::setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
    dataHandler->setGeometry(posX, posY, width, height);
}

void GLFWSurface::setOpenGLVersion(unsigned int major, unsigned int minor) {
} 

void GLFWSurface::swapBuffers() {
}

void GLFWSurface::show() {
}

void GLFWSurface::close() {
}
