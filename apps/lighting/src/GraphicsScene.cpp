#include <GraphicsScene.hpp>

GraphicsScene::GraphicsScene() :
    camerMatPtr(nullptr), 
    currTime(0.f),
    prevTime(0.f) {
}

GraphicsScene::~GraphicsScene() {
}

void GraphicsScene::setBackgroudColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    glClearColor(r, g, b, a);
}

void GraphicsScene::add(GraphicsItem* itemPtr, const glm::vec3& location) {
    itemPtr->setScene(this);
    itemPtr->setLocation(location);
    elemList.push_back(itemPtr);
}

void GraphicsScene::update(float timeP) {
    for(auto elem : elemList) {
        elem->update();
    }
}

void GraphicsScene::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto elem : elemList) {
        elem->render();
    }
}