#include <IOCameraController.hpp>

#include <cassert>
#include <iostream>

IOCameraController::IOCameraController(Camera* camera) : 
    cameraPtr(camera),
    mouseSensitive(0.2f),
    moveSpeed(10.f),
    currTimeP(0.f),
    prevTimeP(0.f) {
}

IOCameraController::IOCameraController() :
    cameraPtr(nullptr),
    mouseSensitive(0.2f),
    moveSpeed(10.f),
    currTimeP(0.f),
    prevTimeP(0.f) {
}

IOCameraController::~IOCameraController() {
}

void IOCameraController::controll(const MouseEvent& mouseE) {   
    assert(cameraPtr != nullptr && "Nothing to controll");
    if(mouseE.isMoved()) {
        float xoffset =  mouseSensitive * mouseE.getXOffset();
        float yoffset = -mouseSensitive * mouseE.getYOffset();
        cameraPtr->makePitchYawUpdate(yoffset, xoffset);
    }
}

void IOCameraController::controll(const KeyboardEvent& keyE) {
    assert(cameraPtr != nullptr && "Nothing to controll");
    keysStatus[keyE.getKeyCode()] = keyE.isPressed();
}

void IOCameraController::calcCameraPos() {
    for(auto keyInfo : keysStatus) {
        if(!keyInfo.second) {
            // Key not pressed
            continue;
        }
        float tDist = (currTimeP - prevTimeP) * moveSpeed;
        //TODO: Remove hard-coded WSAD
        switch(keyInfo.first) {
        case KeyboardCode::W:
            cameraPtr->makeMoveAtDirection(cameraPtr->getLookAt(), tDist);
            break;
        case KeyboardCode::S:
            cameraPtr->makeMoveAtDirection(cameraPtr->getLookAt(), -tDist);
            break;
        case KeyboardCode::A:
            cameraPtr->makeMoveAtDirection(cameraPtr->getRightVec(), -tDist);
            break;
        case KeyboardCode::D:
            cameraPtr->makeMoveAtDirection(cameraPtr->getRightVec(), tDist);
            break;
        default:
            // ignore
            break;
        }
    }
}

void IOCameraController::addObject(const SceneObject* obj) {
    objList.push_back(obj);
}

void IOCameraController::updateObj(float timeP) {
    static bool inited = false; // TODO: remove this and add method init()
    if(!inited) {
        prevTimeP = timeP;
        currTimeP = timeP;
        inited = true;
    } else {
        prevTimeP = currTimeP;
        currTimeP = timeP;
    }

    calcCameraPos();

    for(auto objPtr : objList) {
        objPtr->setCameraMat(cameraPtr->getProjectMat4f());
    }
}

void IOCameraController::setCamera(Camera* camera) {
    cameraPtr.reset(camera);
}

void IOCameraController::setMouseSensitive(float value) {
    assert(value > 0 && "Negative mouse sensitive");
    mouseSensitive = value;
}

void IOCameraController::setMoveSpeed(float value) {
    assert(value > 0 && "Negative move speed");
    moveSpeed = value;
}