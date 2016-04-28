// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <core/OpenGLApplication.hpp>
#include <core/GLFWSurface.hpp>
#include <core/ResouceManager.hpp>

#include <iostream>
#include <string>
#include <assert.h>
#include <cstdlib>

const int APP_FAIL = -1;
const int APP_OK = 0;

OpenGLApplication::OpenGLApplication(int argc, char* argv[]) :
    surfaceImpl(new GLFWSurface(this)),
    resourceImpl(new ResourceManager(argc, argv)) {
    assert(argc >= 1 && "[App] Required cmd argc for application");
    assert(argv != nullptr && "[App] Require argv for application");
}

OpenGLApplication::~OpenGLApplication() {
    SAFE_DELETE(resourceImpl);
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

void OpenGLApplication::setResourceShadersDir(const char* dirPath) {
    resourceImpl->setShadersDir(dirPath);
}

GLuint OpenGLApplication::loadOpenGLShader(const char* shaderName, GLenum shaderType) {
    GLuint shaderID = 0;
    shaderID = resourceImpl->loadShader(shaderName, shaderType);
    return shaderID;
}

GLuint OpenGLApplication::loadOpenGLProgram(const char* vertShader, const char* fragShader) {
    GLuint programID = 0;
    programID = resourceImpl->loadProgram(vertShader, fragShader);
    return programID;
}

GLuint OpenGLApplication::loadOpenGLProgram(GLuint vertShader, GLuint fragShader) {
    GLuint programID = 0;
    programID = resourceImpl->loadProgram(vertShader, fragShader);
    return programID;
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
