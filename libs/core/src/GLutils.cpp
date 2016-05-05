// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/openGL.hpp>
#include <openGL/GLutils.hpp>

#include <iostream>

const char* getGLerror() {
    GLenum errCode = GL_NO_ERROR;
    if( (errCode = glGetError()) == GL_NO_ERROR) {
        return nullptr;
    }
    const char* errStr = reinterpret_cast<const char*>(gluErrorString(errCode));
    if(errStr != nullptr) {
        return errStr;
    }
    return "Unknown GL error";
}

void printGLerror(const char* location) {
    const char* tStr = getGLerror();
    if(tStr != nullptr) {
        std::cerr << "[" << location << "] GL Error: " << getGLerror() << std::endl;
    }
}