#include <IOCameraController.hpp>

#include <cassert>

IOCameraController::IOCameraController(Camera* camera) : 
    cameraPtr(camera) {
}

IOCameraController::IOCameraController() :
    cameraPtr(nullptr) {
}

IOCameraController::~IOCameraController() {
}

void IOCameraController::controll(const MouseEvent& mouseE) {
}

void IOCameraController::controll(const KeyboardEvent& keyE) {
}

void IOCameraController::setCamera(Camera* camera) {
    cameraPtr.reset(camera);
}

void* IOCameraController::getCameraMat() {
    return nullptr;
}