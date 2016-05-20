#ifndef __GRAPHIC_ITEM_HPP_
#define __GRAPHIC_ITEM_HPP_

#include <openGL/openGL.hpp>

#include <glm/glm.hpp>

class GraphicsScene;

class GraphicsItem {
public:

    GraphicsItem() : scenePtr(nullptr) {}
    virtual ~GraphicsItem() {}

    
    GraphicsScene* scene() { return scenePtr; }
    virtual void setLocation(const glm::vec3& locationP) = 0; 
    virtual void update() = 0;
    virtual void render() = 0;

    void setScene(GraphicsScene* scene)  { scenePtr = scene; }

private:

    GraphicsScene* scenePtr;


};

#endif /* __GRAPHIC_ITEM_HPP_ */