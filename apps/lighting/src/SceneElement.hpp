#ifndef __SCENE_ELEMENT_HPP__
#define __SCENE_ELEMENT_HPP__

#include <Drawable.hpp>
#include <Scene.hpp>

class SceneElement : public Drawable {
public:
    SceneElement() {}
    virtual ~SceneElement() {}

    virtual void translate() = 0;
    virtual void rotate() = 0;
    virtual void scale() = 0;

    virtual void setPosition(const glm::vec3& pos) = 0;

    Scene* getScene() { return parentScene; }

private:

    friend class Scene;
    void setScene(Scene* scenePtr) { parentScene = scenePtr; }

    Scene* parentScene;
};

#endif /* __SCENE_ELEMENT_HPP__ */
