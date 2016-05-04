// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/OpenGLObject.hpp>

#include <cassert>

OpenGLObject::OpenGLObject() : resID(0) {
}

OpenGLObject::~OpenGLObject() {
}

void OpenGLObject::replaceID(OpenGLObject&& object) {
    if(object.resID == resID) {
        return;
    }
    if(resID != 0) {
        if(makeIsBoundCheck(resID)) {
            makeUnbind(resID);
        }
        makeFree(resID);
    }
    resID = object.resID;
    object.resID = 0;
}

void OpenGLObject::holdID(GLuint resourceID) {
    assert(resourceID != 0 && "Try hold invalid openGL resource");
    assert(resID == 0 && "Try hold other openGL resource");
    resID = resourceID;
}

GLuint OpenGLObject::getID() const {
    return resID;
}

bool OpenGLObject::isValid() {
    if(resID == 0) {
        return false;
    }
    return makeCheck(resID);
}

bool OpenGLObject::isBounded() {
    if(resID == 0) {
        return false;
    }
    return makeIsBoundCheck(resID);
}

void OpenGLObject::bind() {
    assert(resID != 0 && "Try use invalid resource");
    if(!makeIsBoundCheck(resID)) {
        makeBind(resID);
    }
}

void OpenGLObject::unbind() {
    assert(resID != 0 && "Try use invalid resource");
    if(makeIsBoundCheck(resID)) {
        makeUnbind(resID);
    }
}