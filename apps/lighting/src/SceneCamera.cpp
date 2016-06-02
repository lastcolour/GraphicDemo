#include <SceneCamera.hpp>

SceneCamera::SceneCamera() : 
    camera(new FlyCamera()) {
}

SceneCamera::~SceneCamera() {
}

void SceneCamera::setAspectRatio(float ratio) {
    camera->setAspectRatio(ratio);
}

const GLfloat* SceneCamera::getCameraMat() {
    return camera->getDataMat4f();
}

void SceneCamera::setPosition(const glm::vec3& pos) {
    camera->setLocation(pos);
}

void SceneCamera::draw() {
}

void SceneCamera::update() {
}

void SceneCamera::translate() {
}

void SceneCamera::rotate() {
}

void SceneCamera::scale() {
}
