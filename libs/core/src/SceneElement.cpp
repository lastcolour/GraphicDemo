// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <graphics/SceneElement.hpp>

SceneElement::SceneElement() {
}

SceneElement::~SceneElement() {
}

void SceneElement::setScene(Scene3D* scene) {
    scenePtr = scene;
}

Scene3D* SceneElement::getScene() {
    return scenePtr;
}

void SceneElement::setPosition(const glm::vec3& pos) {
    position = pos;
}

const glm::vec3& SceneElement::getPosition() const {
    return position;
}

glm::vec3& SceneElement::getPosition() {
    return position;
}