// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <core/OpenGLApplication.hpp>
#include <core/GLFWSurface.hpp>
#include <core/FlyCamera.hpp>
#include <core/Resouce.hpp>

#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>

const int APP_FAIL = -1;
const int APP_OK = 0;

OpenGLApplication::OpenGLApplication(int argc, char* argv[]) :
    surfaceImpl(new GLFWSurface(this)),
    isShouldClose(false) {

    assert(argc >= 1 && "[App] Required cmd argc for application");
    assert(argv != nullptr && "[App] Require argv for application");
    Resource::setResourceDir(argv[0]);
}

OpenGLApplication::~OpenGLApplication() {
    SAFE_DELETE(surfaceImpl);
}

void OpenGLApplication::setSurfaceTitle(const char* title) {
    surfaceImpl->setTitle(title);
}

void OpenGLApplication::setSurfaceGeometry(unsigned int width, unsigned int height) {
    surfaceImpl->setGeometry(width, height);
}

void OpenGLApplication::setSurfaceResizable(bool flag) {
    surfaceImpl->setResizeable(flag);
}

void OpenGLApplication::surfaceSwapBuffers() {
    surfaceImpl->swapBuffers();
}

void OpenGLApplication::setOpenGLVersion(unsigned int major, unsigned int minor) {
    surfaceImpl->setOpenGL(major, minor);
}

void OpenGLApplication::setOpenGLCoreProfile(bool flag) {
    surfaceImpl->setCoreProfile(flag);
}

void OpenGLApplication::setVisibleCursor(bool flag) {
    surfaceImpl->setVisibleCursor(flag);
}

void OpenGLApplication::setDataFolder(const char* path) {
    Resource::setClientResourceDir(path);
}

unsigned int OpenGLApplication::getWidth() const {
    return surfaceImpl->getWidth();
}

unsigned int OpenGLApplication::getHeight() const {
    return surfaceImpl->getHeight();
}


void OpenGLApplication::setAppShouldEnd() {
    isShouldClose = true;
}

float OpenGLApplication::getAppRunDuration() const {
    return surfaceImpl->getShowDuration();
}

void OpenGLApplication::setSurfaceVsynOn(bool flag) {
    surfaceImpl->setVsyncOn(flag);
}

bool OpenGLApplication::isAppRunning() {
    if (!isShouldClose && surfaceImpl->isOpen()) {
        surfaceImpl->sendEvents();
        if(isShouldClose) {
            return false;
        }
        return true;
    }
    return false;
}

int OpenGLApplication::run() {
    if(!surfaceImpl->show()) {
        return APP_FAIL;
    }
    appInitRequest();
    try {

        mainLoop();

    } catch(const std::exception& exc) {
        std::cerr << "[OpenGLApplication] Fatal error when in mainLoop(): " << exc.what() << std::endl;
        return APP_FAIL;
    } catch(...) {
        std::cerr << "[OpenGLApplication] Unexpected error in mainLoop()!" << std::endl;
        return APP_FAIL;
    }
    return APP_OK;
}
