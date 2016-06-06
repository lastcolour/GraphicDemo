#include <graphics/SceneLight.hpp>

#include <glm/gtc/type_ptr.hpp>

SceneLight::SceneLight() : color(1.f) {
}

SceneLight::~SceneLight() {
}

void SceneLight::setColor(const glm::vec4& color) {
    this->color = color;
}

const glm::vec4& SceneLight::getColor() const {
    return color;
}

glm::vec4& SceneLight::getColor() {
    return color;
}