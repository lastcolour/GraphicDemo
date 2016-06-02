#include <Scene.hpp>
#include <SceneElement.hpp>
#include <SceneCamera.hpp>

#include <openGL/openGL.hpp>

#include <cassert>

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::setViewPort(unsigned int origX, unsigned int origY, unsigned int width, unsigned int height) {
    glViewport(origX, origY, width, height);
    cameraOwner->setAspectRatio(width / float(height));
}

void Scene::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Scene::addElement(SceneElement* elem, const glm::vec3& pos) {
    assert(elem != nullptr && "Added NULL object to scene");
    elem->setScene(this);
    elem->setPosition(pos);
    elements.push_back(elem);
}

void Scene::update() {
    cameraOwner->update();
    for (auto obj : elements) {
        obj->update();
    }
}

void Scene::setCameraOwner(SceneCamera* camPtr, const glm::vec3& pos) {
    assert(camPtr != nullptr && "Set up NULL camera to scene");
    cameraOwner = camPtr;
    cameraOwner->setPosition(pos);
}

void Scene::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::draw() {
    clear();
    cameraOwner->draw();
    for (auto elem : elements) {
        elem->draw();
    }
}

const GLfloat* Scene::getCameraMat() {
    return cameraOwner->getCameraMat();
}
