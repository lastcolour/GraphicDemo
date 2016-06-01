// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/OpenGLObject.hpp>

#include <cassert>

OpenGLObject::OpenGLObject() : objID(0) {
}

OpenGLObject::~OpenGLObject() {
}

GLuint OpenGLObject::getID() const {
    return objID;
}

bool OpenGLObject::isValid() {
    if(objID == 0) {
        return false;
    }
    return true;
    // TODO: Remove?
    // return makeCheck();
}

bool OpenGLObject::isBounded() {
    if(objID == 0) {
        return false;
    }
    return makeIsBoundCheck();
}

void OpenGLObject::bind() {
    assert(objID != 0 && "Try use invalid resource");
    if(!makeIsBoundCheck()) {
        makeBind();
    }
}

void OpenGLObject::unbind() {
    assert(objID != 0 && "Try use invalid resource");
    if(makeIsBoundCheck()) {
        makeUnbind();
    }
}

void OpenGLObject::resetID() {
   if(objID != 0) {
        if(makeIsBoundCheck()) {
            makeUnbind();
        }
        makeFree();
    }
   objID = 0;
}

void OpenGLObject::replaceToID(OpenGLObject&& object) {
    if(object.objID == objID) {
        return;
    }
    if(objID != 0) {
        if(makeIsBoundCheck()) {
            makeUnbind();
        }
        makeFree();
    }
    objID = object.objID;
    object.objID = 0;
}