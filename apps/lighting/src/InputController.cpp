#include <InputController.hpp>

InputController::InputController() {
}

InputController::~InputController() {
}

void InputController::setMouseSensetive(float value) {
}

void InputController::controll(const KeyboardEvent& inpEvent) {
    keysPressStatus[inpEvent.getKeyCode()] = inpEvent.isPressed();
}

void InputController::controll(const MouseEvent& inpEvent) {
    if (inpEvent.isMoved()) {
        float xoffset =  mouseSensetive * inpEvent.getXOffset();
        float yoffset = -mouseSensetive * inpEvent.getYOffset();
        //camera->makePitchYawUpdate(yoffset, xoffset);
    }
}

void InputController::process(float deltaTime) {
    for (auto keyStatus : keysPressStatus) {
        if (!keyStatus.second) {
            // Key not pressed
            continue;
        }
        float moveSpeed = 5.f;
        float tDist = (deltaTime) * moveSpeed;
        switch (keyStatus.first) {
        case KeyboardCode::R:
            break;
        case KeyboardCode::W:
            // camera->makeMoveAtDirection(camera->getLookAt(), tDist);
            break;
        case KeyboardCode::S:
            // camera->makeMoveAtDirection(camera->getLookAt(), -tDist);
            break;
        case KeyboardCode::A:
            // camera->makeMoveAtDirection(camera->getRightVec(), -tDist);
            break;
        case KeyboardCode::D:
            // camera->makeMoveAtDirection(camera->getRightVec(), tDist);
            break;
        default:
            // ignore
            break;
        }
    }
}