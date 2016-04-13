#include <core/GLFWDataHandler.hpp>

GLFWDataHandler::GLFWDataHandler() {
}

GLFWDataHandler::~GLFWDataHandler() {
}

void GLFWDataHandler::setColorMode(SurfaceColorMode mode) {
}

void GLFWDataHandler::setBufferMode(SurfaceBufferMode mode) {
}

void GLFWDataHandler::setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
}

void GLFWDataHandler::setTitle(const std::string& title) {
}

void GLFWDataHandler::setOpenGLContexVersion(unsigned int major, unsigned int minor) {
    glContexMajorVersion = major;
    glContexMinorVersion = minor;
}

int GLFWDataHandler::getOpenGLContexMajorVersion() {
    return glContexMajorVersion;
}

int GLFWDataHandler::getOpenGLContexMinorVersion() {
    return glContexMinorVersion;
}