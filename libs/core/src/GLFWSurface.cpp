// author: Oleksii Zhogan

#include <openGL/openGL.hpp>

#include <core/OpenGLApplication.hpp>
#include <core/GLFWSurface.hpp>
#include <core/KeyboardEvent.hpp>

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <assert.h>

bool GLFWSurface::GLFW_LIB_INITED = false;
bool GLFWSurface::GLEW_LIB_INITED = false;

GLFWSurface::GLFWSurface(VisualApplication* app) :
    Surface(app),
    title("Surface"),
    windowPtr(nullptr),
    width(600),
    height(400),
    openGLMajor(3),
    openGLMinor(3),
    resizeable(true),
    corePorfile(true) {

    if(!GLFW_LIB_INITED) {
        GLFW_LIB_INITED = glfwInit() == GL_TRUE;
        assert(GLFW_LIB_INITED && "GLFW Lib should be initialized");
    }
}

GLFWSurface::~GLFWSurface() {
    if(!windowPtr) {
        glfwDestroyWindow(windowPtr);
    }
    if(GLFW_LIB_INITED) {
        glfwTerminate();
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

void GLFWSurface::sendEvents() {
    glfwPollEvents();
}

bool GLFWSurface::isOpen() {
    if(windowPtr) {
        if(glfwWindowShouldClose(windowPtr) != GL_TRUE) {
            return true;
        }
        windowPtr = nullptr;
    }
    return false;
}

void GLFWSurface::swapBuffers() {
    if(windowPtr) {
        glfwSwapBuffers(windowPtr);
    }
}

void GLFWSurface::close() {
    if(windowPtr) {
        glfwSetWindowShouldClose(windowPtr, GL_TRUE);
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
        // Check openGL status
        errCode = GL_NO_ERROR;
        if((errCode = glGetError()) != GL_NO_ERROR) {
            // Ignore invalid enum
            if(errCode == GL_INVALID_ENUM) {
                return true;
            }
            std::cerr << "[GLEW] OpenGL error: " << reinterpret_cast<const char*>(gluErrorString(errCode)) << std::endl; 
            return false;
        }
        GLEW_LIB_INITED = true;
    }
    return true;
}

void GLFWSurface::keyboardCallback(GLFWwindow* windowPtr, int keyCode, int scanCode, int action, int keyMode) {

    KeyCode code = KeyCode::UNKNOWN;
    KeyType type = KeyType::UNKNOWN;

    switch (keyCode)
    {
    case GLFW_KEY_R:
        code = KeyCode::R;
        break;
    default:
        code = KeyCode::UNKNOWN;
        break;
    }

    switch (action)
    {
    case GLFW_PRESS:
        type = KeyType::PRESSED;
        break;
    case GLFW_RELEASE:
        type = KeyType::RELEASE;
        break;
    case GLFW_REPEAT:
        type = KeyType::REPEAT;
        break;
    default:
        type = KeyType::UNKNOWN;
        break;
    }

    KeyboardEvent keyEvent(code, type);
    if (keyMode & GLFW_MOD_ALT) {
        keyEvent.setAltPressed(true);
    } else if (keyMode & GLFW_MOD_CONTROL) {
        keyEvent.setCtrlPressed(true);
    } else if (keyMode & GLFW_MOD_SHIFT) {
        keyEvent.setShiftPressed(true);
    }

    Surface::sendKeyboardEvent(keyEvent);
}

void GLFWSurface::initCallbacks() {
    assert(windowPtr != nullptr && "Can't create callback without windwows");
    glfwSetKeyCallback(windowPtr, keyboardCallback);
}

bool GLFWSurface::show() {
    if(windowPtr) {
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

    windowPtr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!windowPtr) {
        return false;
    }
    glfwMakeContextCurrent(windowPtr);
    if(!initGLEW()) {
        glfwDestroyWindow(windowPtr);
        return false;
    }
    initCallbacks();
    sendResizeEvent(width, height);
    return true;
}
