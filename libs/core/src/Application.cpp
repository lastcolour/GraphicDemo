// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>

#include <exception>
#include <iostream>
#include <string>

const int APP_FAIL = -1;
const int APP_OK = 0;

Application::Application(int argc, char* argv[]) :
    surfacePtr(new GLFWSurface(this)) {
}

Application::~Application() {
}

Surface* Application::getSurface() {
    return surfacePtr.get();
}

bool Application::appInit() {
    if(surfacePtr->show()) {
        onInitEvent();
        return true;
    }
    return false;
}

void Application::onInitEvent() {
}

void Application::onDeinitEvent() {
}

void Application::onDrawEvent() {
}

void Application::onResizeEvent(unsigned int width, unsigned int height) {
}

int Application::run() {
    if(!appInit()) {
        return APP_FAIL;
    }
    try {
        mainLoop();
    } catch(std::exception& e) {
        std::cerr << "[App] Unexpected problem when run app: " << e.what() << std::endl;
        return APP_FAIL;
    } catch( ... ) {
        return APP_FAIL;
    }
    return APP_OK;
}

void Application::mainLoop() {
    while(surfacePtr->isOpen()) {
        surfacePtr->sendInputEvents();
        onDrawEvent();
    }
}
