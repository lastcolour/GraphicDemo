// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL

#include "Application.hpp"
#include "ModelLoader.hpp"
#include "Simulation.hpp"
#include "EarthPhysic.hpp"
#include "Logger.hpp"

#include <mutex>
#include <cassert>
#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GL version
const int GL_MAJOR_VER = 3;
const int GL_MINOR_VER = 3;

// Surface predefined values
const char* SF_TITLE     = "DevUBI";
const int   SF_WIDTH     = 800;
const int   SF_HEIGHT    = 600;
const bool  SF_RESIZEBLE = false; // there is no perspective corrections
 
// application log
const char* LOG_FILE = "log.txt";
const char* HELP_MSG = "Control:\n"\
                       "\tTo restart simulation press key: <R>\n"\
                       "\tTo finish use press <ESC>";

int APP_OK = 0;
int APP_FAIL = 1;

Application* Application::ACTIVE_APP = nullptr;
bool Application::GLFW_INITED = false;

Application::Application(int argc, char* argv[]) :
    windowPtr(nullptr),
    simulPtr(nullptr),
    currTimeP(0.f),
    prevTimeP(0.f) {

    assert(ACTIVE_APP == nullptr && "Only one application can be created");
    ACTIVE_APP = this;

    Logger::info("Help", HELP_MSG);

    Logger::getInstance().addFileStream(LOG_FILE);
    Logger::info("Application", "Log file will be saved to: ", LOG_FILE);

    if (!load(argc, argv) || !initGraphics()) {
        // nothing to do here
        Logger::error("Application", "Fail to initialize!");
        std::exit(APP_FAIL);
    }
}

Application::~Application() {
    if (!windowPtr && GLFW_INITED) {
        glfwDestroyWindow(windowPtr);
    }
    if (GLFW_INITED) {
        glfwTerminate();
    }
}

void Application::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    assert(ACTIVE_APP != nullptr && "Surface without application");
    if(key == GLFW_KEY_R && action == GLFW_RELEASE) {
        ACTIVE_APP->restart();
    } else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        Logger::debug("Application", "User ask about exit");
        glfwSetWindowShouldClose(window, true);
    }
}

void Application::initCallbacks() {
    glfwSetKeyCallback(windowPtr, keyboardCallback);
}

bool Application::initGraphics() {
    GLFW_INITED = glfwInit() == GL_TRUE;
    if (!GLFW_INITED) {
        return false;
    }
    if (!initSurface()) {
        return false;
    }
    if (!initGLEW()) {
        return false;
    }
    initCallbacks();
    return true;
}

bool Application::initGLEW() {
    glewExperimental = GL_TRUE;
    GLenum errCode = GL_NO_ERROR;
    if ((errCode = glewInit()) != GLEW_OK) {
        const GLubyte* errStr = glewGetErrorString(errCode);
        Logger::error("Application", "GLEW init error: ", reinterpret_cast<const char*>(errStr));
        return false;
    }
    // Check openGL status
    errCode = GL_NO_ERROR;
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        // Ignore invalid enum
        if (errCode == GL_INVALID_ENUM) {
            return true;
        }
        Logger::error("Application", "GLEW init error: ", reinterpret_cast<const char*>(gluErrorString(errCode)));
        return false;
    }
    return true;
}

bool Application::load(int argc, char* argv[]) {
    ModelLoader tLoader;
    Physics* tPhysic = new EarthPhysics(tLoader.load(argc ,argv));
    if (!tPhysic->isValid()) {
        Logger::error("Application", "Loaded invalid physic");
        delete tPhysic;
        return false;
    }
    simulPtr.reset(new Simulation(tPhysic));
    return true;
}

bool Application::initSurface() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VER);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR_VER);
    glfwWindowHint(GLFW_RESIZABLE, SF_RESIZEBLE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    windowPtr = glfwCreateWindow(SF_WIDTH, SF_HEIGHT, SF_TITLE, nullptr, nullptr);
    simulPtr->setViewPort(SF_WIDTH, SF_HEIGHT);

    if (!windowPtr) {
        return false;
    }
    glfwMakeContextCurrent(windowPtr);
    if (!initGLEW()) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
        return false;
    }
    glfwSetTime(0.F);
    return true;
}

void Application::restart() {
    if(simulPtr != nullptr) {
        Logger::info("Application", "Restart simulation");
        simulPtr->restart();
    }
}

int Application::run() {
    if (!windowPtr || !simulPtr) {
        // No reason to start
        return APP_FAIL;
    }
    if (!simulPtr->init()) {
        Logger::error("Application", "Can't init simulation. Terminate.");
        return APP_FAIL;
    }
    currTimeP = static_cast<float>(glfwGetTime());
    prevTimeP = currTimeP;
    try {
        // main Loop
        while (!glfwWindowShouldClose(windowPtr)) {
            prevTimeP = currTimeP;
            currTimeP = static_cast<float>(glfwGetTime());
            simulPtr->update(currTimeP - prevTimeP);
            simulPtr->draw();

            glfwSwapBuffers(windowPtr);
            glfwPollEvents();
        }
    } catch (std::exception& e) {
        Logger::error("Application", "Unexpected error in main loop: ", e.what());
        return APP_FAIL;
    } catch (...) {
        Logger::error("Application", "Unknown error in main loop.");
        return APP_FAIL;
    }
    return APP_OK;
}
