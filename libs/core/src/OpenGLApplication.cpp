// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <core/OpenGLApplication.hpp>
#include <core/GLFWSurface.hpp>
#include <core/Resouce.hpp>

#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>

const int APP_FAIL = -1;
const int APP_OK = 0;

OpenGLApplication::OpenGLApplication(int argc, char* argv[]) :
    surfaceImpl(new GLFWSurface(this)) {
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

void OpenGLApplication::checkInitErrors() {
    reportGLerrors("onInit");
}

void OpenGLApplication::checkResizerrors() {
    reportGLerrors("onResize");
}

void OpenGLApplication::checkKeyboardErrors() {
    reportGLerrors("onKeyboard");
}

void OpenGLApplication::checkDrawErrors() {
    reportGLerrors("onDraw");
}

void OpenGLApplication::setDataFolder(const char* path) {
    Resource::setClientResourceDir(path);
}

void OpenGLApplication::reportGLerrors(const char* location) {
    std::string tMesagePrefix = "[App:";
    tMesagePrefix = tMesagePrefix + location + "]";
    GLenum errCode = GL_NO_ERROR;
    if( (errCode = glGetError()) != GL_NO_ERROR) {
        GLint infoLog = 0;
        const char* errStr = reinterpret_cast<const char*>(gluErrorString(errCode));
        if(errStr != nullptr) {
            std::cerr << tMesagePrefix  << " GL error: " << errStr << std::endl;
        } else {
            std::cerr << tMesagePrefix << " Unknown GL error" << std::endl;
        }
    } else {
        // Spam
        // std::cout << tMesagePrefix <<  " Success" << std::endl;
    }
}

int OpenGLApplication::run() {
    surfaceImpl->show();
    appInitRequest();
    while(surfaceImpl->isOpen()) {
        // TODO: Reimplement this method
        surfaceImpl->sendEvents();
        appDrawRequest();
    }
    return APP_OK;
}
