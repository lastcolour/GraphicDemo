// author: Oleksii Zhogan


#include <openGL/GLutils.hpp>
#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>

#include <exception>
#include <iostream>
#include <string>
#include <assert.h>

const int APP_FAIL = -1;
const int APP_OK = 0;

Application* Application::appInstance = nullptr;

Application::Application(int argc, char* argv[]) :
    errCode(APP_OK),
    surfacePtr(new GLFWSurface()),
    resourcePtr() {
    assert(appInstance == nullptr && "[App] Only one app instance allowed");
    assert(argc >= 1 && "[App] Required cmd argc for application");
    assert(argv != nullptr && "[App] Require argv for application");
    appInstance = this;
    resourcePtr = new ResourceManager(argv[0]);
}

Application::~Application() {
    SAFE_DELETE(surfacePtr);
    SAFE_DELETE(resourcePtr);
    appInstance = nullptr;
}

Application* Application::getInstance() {
    assert(appInstance != nullptr && "[App] Create app intance before");
    return appInstance;
}

ResourceManager* Application::getResourceManager() const {
    return resourcePtr;
}

Surface* Application::getSurface() {
    return surfacePtr;
}

int Application::getErrorCode() const{
    return errCode;
}

void Application::setErrorCode(int errCode) {
    this->errCode = errCode;
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

void Application::finishApp(int errCode, const char* lastMessage) {
    // TODO: Implement this function
    surfacePtr->close();
    setErrorCode(errCode);
}

int Application::run() {
    if(!appInit()) {
        setErrorCode(APP_FAIL);
    }
    try {
        mainLoop();
    } catch(std::exception& e) {
        std::cerr << "[App] Unexpected problem when run app: " << e.what() << std::endl;
        setErrorCode(APP_FAIL);
    } catch( ... ) {
        setErrorCode(APP_FAIL);
    }
    return getErrorCode();
}

void Application::drawEvent() {
    onDrawEvent();
}

void Application::mainLoop() {
    while(surfacePtr->isOpen()) {
        surfacePtr->sendInputEvents();
        drawEvent();
    }
}