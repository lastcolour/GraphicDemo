#include <core/GLEWManager.hpp>
#include <GL/glew.h>

bool GLEWManager::initialize() {
    glewExperimental = GL_TRUE;
    return  glewInit() == GLEW_OK;
}

bool GLEWManager::deinitialize() {
    // nothing to do here
    return true;
}