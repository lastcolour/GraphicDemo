#include "Application.hpp"
#include "ArgParser.hpp"
#include "Simulation.hpp"

#include "EarthPhysic.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

// GL version
const int GL_MAJOR_VER = 3;
const int GL_MINOR_VER = 3;

// Surface predefined values
const char* SF_TITLE     = "DevUBI";
const int   SF_WIDTH     = 800;
const int   SF_HEIGHT    = 600;
const bool  SF_RESIZEBLE = false; // there is no perspective corrections
 
int APP_OK = 0;
int APP_FAIL = 1;

bool Application::GLFW_INITED = false;

float currTimeP;
float prevTimeP;

Application::Application(int argc, char* argv[]) :
    windowPtr(nullptr) {

    parseArgs(argc, argv);

    if (!initGraphics()) {
        // nothing to do here
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

void Application::initCallbacks() {
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
    return true;
}

bool Application::initGLEW() {
    glewExperimental = GL_TRUE;
    GLenum errCode = GL_NO_ERROR;
    if ((errCode = glewInit()) != GLEW_OK) {
        const GLubyte* errStr = glewGetErrorString(errCode);
        std::cerr << "[Application] GLEW init error: " << reinterpret_cast<const char*>(errStr) << std::endl;
        return false;
    }
    // Check openGL status
    errCode = GL_NO_ERROR;
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        // Ignore invalid enum
        if (errCode == GL_INVALID_ENUM) {
            return true;
        }
        std::cerr << "[Application] OpenGL error: " << reinterpret_cast<const char*>(gluErrorString(errCode)) << std::endl;
        return false;
    }
    return true;
}

bool Application::parseArgs(int argc, char* argv[]) {
    ArgParser tParser;
    Physics* tPhysic = new EarthPhysics(tParser.parse(argc, argv));
    if (!tPhysic->isValid()) {
        std::cout << "[Application] Loaded invalid physic" << std::endl;
        std::cout << "[Application] Problem: " << tPhysic->getInvalidError() << std::endl;
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

int Application::run() {
    if (!windowPtr) {
        // No reason to draw without suface
        return APP_FAIL;
    }
    currTimeP = static_cast<float>(glfwGetTime());
    prevTimeP = currTimeP;
    if (!simulPtr->init()) {
        return APP_FAIL;
    }
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
    } catch (...) {
        return APP_FAIL;
    }
    return APP_OK;
}