#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <Drawable.hpp>

#include <openGL/openGL.hpp>

#include <glm/glm.hpp>

#include <vector>

class SceneCamera;
class SceneElement;


class Scene : public Drawable {
public:

    Scene();
    virtual ~Scene();

    virtual void setCameraOwner(SceneCamera* cameraOwner, const glm::vec3& pos);
    virtual void setViewPort(unsigned int origX, unsigned int origY, unsigned int width, unsigned int height);
    virtual void setClearColor(float r, float g, float b, float a = 0.f);

    virtual void addElement(SceneElement* item, const glm::vec3& pos);

    virtual void clear();
    virtual void update();
    virtual void draw();

    const GLfloat* getCameraMat();

private:

    SceneCamera* cameraOwner;
    std::vector<SceneElement*> elements;

};

#endif /* __SCENE_HPP__ */