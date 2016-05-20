// author: Oleksii Zhogan (alexzhogan@gmail.com)

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
bool GLFWSurface::MOUSE_IN_FOCUS = false;
MouseEvent GLFWSurface::LAST_MOUSE_EVENT = MouseEvent(0.f, 0.f, MouseKeyCode::NONE, EventType::NONE);

GLFWSurface::GLFWSurface(VisualApplication* app) :
    Surface(app),
    title("Surface"),
    windowPtr(nullptr),
    width(600),
    height(400),
    openGLMajor(3),
    openGLMinor(3),
    resizeable(true),
    corePorfile(true),
    isDisabledCursor(false),
    isVsyncOn(false) {

    if(!GLFW_LIB_INITED) {
        GLFW_LIB_INITED = glfwInit() == GL_TRUE;
        assert(GLFW_LIB_INITED && "GLFW Lib should be initialized");
    }
}

GLFWSurface::~GLFWSurface() {
    if(!windowPtr) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
    }
    if(GLFW_LIB_INITED) {
        glfwTerminate();
        GLFW_LIB_INITED = false;
    }
}

void GLFWSurface::setTitle(const char* title) {
    assert(title != nullptr && "Invalid title");
    this->title = title;
}

void GLFWSurface::setGeometry(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void GLFWSurface::setResizeable(bool flag) {
    resizeable = flag;
}

void GLFWSurface::setVsyncOn(bool flag) {
    isVsyncOn = flag;
}

void GLFWSurface::setOpenGL(unsigned int major, unsigned int minor) {
    openGLMajor = static_cast<int>(major);
    openGLMinor = static_cast<int>(minor);
}

void GLFWSurface::setCoreProfile(bool flag) {
    corePorfile = flag;
}

void GLFWSurface::setVisibleCursor(bool flag) {
    isDisabledCursor = flag;
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

unsigned int GLFWSurface::getWidth() const {
    return width;
}

unsigned int GLFWSurface::getHeight() const {
    return height;
}

float GLFWSurface::getShowDuration() const {
    return static_cast<float>(glfwGetTime());
}

void GLFWSurface::windowRefreshCallback(GLFWwindow* windowPtr) {
    Surface::sendReDrawEvent();
}

void GLFWSurface::windowFramebufferResizeCallback(GLFWwindow* windwoPtr, int width, int height) {
    Surface::sendResizeEvent(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void GLFWSurface::keyboardCallback(GLFWwindow* windowPtr, int keyCode, int scanCode, int action, int keyMode) {

    KeyboardCode code = KeyboardCode::UNKNOWN;
    EventType type = EventType::UNKNOWN;

    switch (keyCode)
    {

    case GLFW_KEY_R:
        code = KeyboardCode::R;
        break;
    case GLFW_KEY_W:
        code = KeyboardCode::W;
        break;
    case GLFW_KEY_S:
        code = KeyboardCode::S;
        break;
    case GLFW_KEY_D:
        code = KeyboardCode::D;
        break;
    case GLFW_KEY_A:
        code = KeyboardCode::A;
        break;
    case GLFW_KEY_ESCAPE:
        code = KeyboardCode::ESC;
        break;
    default:
        code = KeyboardCode::UNKNOWN;
        break;
    }

    switch (action)
    {
    case GLFW_PRESS:
        type = EventType::PRESSED;
        break;
    case GLFW_RELEASE:
        type = EventType::RELEASE;
        break;
    case GLFW_REPEAT:
        type = EventType::REPEAT;
        break;
    default:
        type = EventType::UNKNOWN;
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

void GLFWSurface::mouseFocusCallback(GLFWwindow* window, int entered) {
    MOUSE_IN_FOCUS = entered != 0;
}

void GLFWSurface::mousePosCallback(GLFWwindow* window, double x, double y) {
    MouseEvent tEvent(static_cast<float>(x), static_cast<float>(y), MouseKeyCode::NONE, EventType::MOVE);
    tEvent.setTime(static_cast<float>(glfwGetTime()));
    // Do not jump
    if(MOUSE_IN_FOCUS) {
        tEvent.setPrevEvent(LAST_MOUSE_EVENT);
    }
    LAST_MOUSE_EVENT = tEvent;

    Surface::sendMouseEvent(tEvent);
}

void GLFWSurface::mouseButtonCallback(GLFWwindow* window, int mouseButton, int action, int keyMode) {
    EventType type;
    switch (action)
    {
    case GLFW_PRESS:
        type = EventType::PRESSED;
        break;
    case GLFW_RELEASE:
        type = EventType::RELEASE;
        break;
    case GLFW_REPEAT:
        type = EventType::REPEAT;
        break;
    default:
        type = EventType::UNKNOWN;
        break;
    }
    MouseEvent tEvent(static_cast<float>(0.f), static_cast<float>(0.f), MouseKeyCode::NONE, type);
    Surface::sendMouseEvent(tEvent);
}

void GLFWSurface::mouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}

void GLFWSurface::initCallbacks() {
    assert(windowPtr != nullptr && "Can't create callback without windwows");
    // Window
    glfwSetWindowRefreshCallback(windowPtr, windowRefreshCallback);
    glfwSetFramebufferSizeCallback(windowPtr, windowFramebufferResizeCallback);
    // Keyboard
    glfwSetKeyCallback(windowPtr, keyboardCallback);
    // Mouse
    glfwSetCursorEnterCallback(windowPtr, mouseFocusCallback);
    glfwSetMouseButtonCallback(windowPtr, mouseButtonCallback);
    glfwSetCursorPosCallback(windowPtr, mousePosCallback);
    glfwSetScrollCallback(windowPtr, mousePosCallback);
}

bool GLFWSurface::show() {
    // TODO: split this function to several
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
#ifdef GD_CORE_LIB_DEBUG
        std::cerr << "[Surface] Can't create GLFWSurface";
        std::cerr << "\n[Surface] Required openGL version: " << openGLMajor << "." << openGLMinor << std::endl;
#endif /* GD_CORE_LIB_DEBUG */
        return false;
    }
    if(isDisabledCursor) {
        glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    glfwMakeContextCurrent(windowPtr);
    if(!initGLEW()) {
#ifdef GD_CORE_LIB_DEBUG
        std::cerr << "[Surface] Can't initialize GLEW";
        std::cerr << "\n[Surface] Required openGL version: " << openGLMajor << "." << openGLMinor << std::endl;
#endif /* GD_CORE_LIB_DEBUG */
        glfwDestroyWindow(windowPtr);
        return false;
    }
    initCallbacks();

    if(isVsyncOn) {
        glfwSwapInterval(1);
    }
    glfwSetTime(0.F);
    Surface::sendResizeEvent(width, height);
    return true;
}