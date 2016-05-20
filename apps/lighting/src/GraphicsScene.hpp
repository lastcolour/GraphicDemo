#ifndef __GRAPHICS_SCENE_HPP__
#define __GRAPHICS_SCENE_HPP__

#include <GraphicsItem.hpp>
#include <IOCameraController.hpp>

#include <glm/glm.hpp>

#include <vector>

class GraphicsScene {
public:

    GraphicsScene();
    ~GraphicsScene();

    void setBackgroudColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void add(GraphicsItem* itemPtr, const glm::vec3& location = glm::vec3(0));

    void update(float timeP);
    void render();
    
    const GLfloat* cameraMat() const;
    const float waitForUpdate() const;

private:

    std::vector<GraphicsItem*> elemList;
    GLfloat* camerMatPtr;
    float prevTime;
    float currTime;
};

#endif /* __GRAPHICS_SCENE_HPP__*/