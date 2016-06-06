// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <graphics/Drawable.hpp>
#include <graphics/Math3D.hpp>

#include <openGL/openGL.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <map>

class SceneElement;
class SceneLight;
class SceneCamera;

class LIB_EXPORT_CONV Scene3D : public Drawable {
public:

    Scene3D();
    virtual ~Scene3D();

    virtual void setViewArea(float origX, float origY, float width, float height);
    virtual void setClearColor(float r, float g, float b, float a);
    virtual void setCamera(SceneCamera* camera, const glm::vec3& pos);
    
    virtual SceneCamera* getCamera();
    virtual const GLfloat* getCameraMat();
    const std::vector<SceneLight*>& getLights() const;

    virtual void addElement(SceneElement* elem, const glm::vec3& pos);
    virtual void addLight(SceneLight* light, const glm::vec3& pos);

    virtual void clear();
    virtual void update();
    virtual void render();

private:
     
    std::vector<SceneElement*> elements;
    std::vector<SceneLight*> lights;
    Quad viewBox;
    SceneCamera* cameraPtr;

};

#endif /* __SCENE_HPP__ */