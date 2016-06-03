#include <graphics/Scene3D.hpp>
#include <graphics/SceneElement.hpp>
#include <graphics/SceneCamera.hpp>

#include <cassert>

Scene3D::Scene3D() : Drawable(),
    elements(),
    cameraPtr(nullptr) {
}

Scene3D::~Scene3D() {
}

void Scene3D::add(SceneElement* elem, const glm::vec3& position) {
    assert(elem != nullptr && "Add NULL element to scene");
    elem->setScene(this);
    elem->setPosition(position);
    elements.push_back(elem);
}

void Scene3D::setCamera(SceneCamera* camera, const glm::vec3& position) {
    assert(camera != nullptr && "Set NULL camera for scene");
    camera->setScene(this);
    camera->setPosition(position);
    cameraPtr = camera;
}

SceneCamera* Scene3D::getCamera() {
    return cameraPtr;
}

const GLfloat* Scene3D::getCameraMat() {
    if (cameraPtr != nullptr) {
        return cameraPtr->getMatrixPtr();
    }
    return nullptr;
}

void Scene3D::update() {
    cameraPtr->update();
    for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
        (*it)->update();
    }
}

void Scene3D::render() {
    cameraPtr->render();
    for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
        (*it)->render();
    }
}