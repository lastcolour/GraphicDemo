#include <graphics/Scene3D.hpp>
#include <graphics/SceneElement.hpp>
#include <graphics/SceneCamera.hpp>

#include <cassert>

Scene3D::Scene3D() : Drawable(),
    elements(),
    viewBox(),
    cameraPtr(nullptr) {

    glEnable(GL_DEPTH_TEST); // TODO: need check for valid openGL contex before any GL call in constructor
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

void Scene3D::setViewArea(float origX, float origY, float width, float height) { 
    assert(origX > 0 && origY > 0 && width > 0 && height > 0 && "Invalid view area for sceen");
    viewBox = Quad(origX, origY, width, height); // Without scissor test this code is redundat
    cameraPtr->setAspectRatio(width / height);
}

void Scene3D::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
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

void Scene3D::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene3D::update() {
    cameraPtr->update();
    for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
        (*it)->update();
    }
}

void Scene3D::render() {
    clear();
    cameraPtr->render();
    for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
        (*it)->render();
    }
}