#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <graphics/Drawable.hpp>

#include <openGL/openGL.hpp>

#include <glm/glm.hpp>

#include <vector>

class SceneElement;
class SceneCamera;

class LIB_EXPORT_CONV Scene3D : public Drawable {
public:

    Scene3D();
    virtual ~Scene3D();

    virtual void setCamera(SceneCamera* camera, const glm::vec3& pos);

    virtual SceneCamera* getCamera();
    virtual const GLfloat* getCameraMat();

    virtual void add(SceneElement* elem, const glm::vec3& pos);

    virtual void update();
    virtual void render();

private:

    std::vector<SceneElement*> elements;
    SceneCamera* cameraPtr;

};

#endif /* __SCENE_HPP__ */