// author: Oleksii Zhogan


#include <core/OpenGLApplication.hpp>
#include <core/GLFWSurface.hpp>
#include <core/ResouceManager.hpp>

#include <exception>
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

int OpenGLApplication::run() {
    surfaceImpl->show();
    onInitEvent();
    while(surfaceImpl->isOpen()) {
        surfaceImpl->sendEvents();
        onDrawEvent();
    }
    return 0;
}
