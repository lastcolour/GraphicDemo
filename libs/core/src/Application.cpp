// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>
#include <core/GLEWManager.hpp>

#include <exception>
#include <iostream>
#include <string>

const int APP_FAIL = -1;
const int APP_OK = 0;

Application::Application(int argc, char* argv[]) {
    if(!initializeApp()) {
        std::cerr << "Application terminated." << std::endl;
        std::exit(APP_FAIL);
    }
}

Application::~Application() {
    if(!deinitializeApp()) {
        std::cerr << "Application terminated." << std::endl;
        std::exit(APP_FAIL); 
    }
}

bool Application::initializeApp() {
    if(!GLEWManager::initialize()) {
        std::cerr << "Can't initialize GLEW." << std::endl;
        return false;
    }
    if(!GLFWSurface::initialize()) {
        std::cerr << "Can't initialize surface manager." << std::endl;
        return false;
    }
    return true;
}

bool Application::deinitializeApp() {
    if(!GLEWManager::initialize()) {
        std::cerr << "Can't initialize GLEW." << std::endl;
        return false;
    }
    if(!GLFWSurface::initialize()) {
        std::cerr << "Can't initialize surface manager." << std::endl;
        return false;
    }
    return true;
}

int Application::run() {
    try {
        mainLoop();
    } catch(std::exception& e) {
        std::cerr << "Problem: " << e.what() << std::endl;
        return APP_FAIL;
    } catch( ... ) {
        return APP_FAIL;
    }
    return APP_OK;
}

void Application::mainLoop() {
}
