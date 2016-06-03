#ifndef __SCENE_ELEMENT_HPP__
#define __SCENE_ELEMENT_HPP__

#include <graphics/Drawable.hpp>

#include <graphics/Scene3D.hpp>

#include <glm/glm.hpp>

class LIB_EXPORT_CONV SceneElement : public Drawable {
public:

    SceneElement();
    virtual ~SceneElement();

    void setScene(Scene3D* scene);
    Scene3D* getScene();

    void setPosition(const glm::vec3& pos);
    const glm::vec3& getPosition() const;
    glm::vec3& getPosition();

private:

    glm::vec3 position;
    Scene3D* scenePtr;
};

#endif /* __SCENE_ELEMENT_HPP__ */