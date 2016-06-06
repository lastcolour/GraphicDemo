// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <InputController.hpp>

#include <graphics/SceneCamera.hpp>

#include <iostream>

InputController::InputController() :
    keysPressStatus(),
    mouseSensetive(0.2f),
    moveSpeed(10.f) {
}

InputController::~InputController() {
}

void InputController::setMouseSensetive(float value) {
    mouseSensetive = value;
}

void InputController::setMoveSpeed(float value) {
    moveSpeed = value;
}

void InputController::setSceneToControll(Scene3D* scene) {
    scenePtr = scene;
}

void InputController::controll(const KeyboardEvent& inpEvent) {
    keysPressStatus[inpEvent.getKeyCode()] = inpEvent.isPressed();
}

void InputController::controll(const MouseEvent& inpEvent) {
    SceneCamera* tCamera = scenePtr->getCamera();
    if (inpEvent.isMoved()) {
        float xoffset =  mouseSensetive * inpEvent.getXOffset();
        float yoffset = -mouseSensetive * inpEvent.getYOffset();
        tCamera->makePitchYawUpdate(yoffset, xoffset);
    }
}

void InputController::process(float deltaTime) {
    SceneCamera* tCamera = scenePtr->getCamera();
    for (auto keyStatus : keysPressStatus) {
        if (!keyStatus.second) {
            // Key not pressed
            continue;
        }
        float tDist = (deltaTime) * moveSpeed;
        switch (keyStatus.first) {
        case KeyboardCode::R:
            break;
        case KeyboardCode::W:
            tCamera->makeMoveAtDirection(tCamera->getLookAt(),    tDist);
            break;
        case KeyboardCode::S:
            tCamera->makeMoveAtDirection(tCamera->getLookAt(),   -tDist);
            break;
        case KeyboardCode::A:
            tCamera->makeMoveAtDirection(tCamera->getRightVec(), -tDist);
            break;
        case KeyboardCode::D:
            tCamera->makeMoveAtDirection(tCamera->getRightVec(),  tDist);
            break;
        case KeyboardCode::SPACE:
            tCamera->makeMoveAtDirection(tCamera->getUpVec(), tDist);
            break;
        default:
            //ignore
            break;
        }
    }
}