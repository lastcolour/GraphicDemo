#include <core\GLEWManager.hpp>

#include <GL\glew.h>

GLEWManager::GLEWManager() {
}

GLEWManager::~GLEWManager() {
}

bool GLEWManager::initialize() {
    glewExperimental = GL_TRUE;
    return  glewInit() == GLEW_OK;
}