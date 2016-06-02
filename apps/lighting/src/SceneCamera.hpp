#ifndef __SCENE_CAMERA_HPP__
#define __SCENE_CAMERA_HPP__

#include <SceneElement.hpp>

#include <core/FlyCamera.hpp>

#include <openGL/openGL.hpp>

#include <memory>

class SceneCamera : public SceneElement {
public:

    SceneCamera();
    virtual ~SceneCamera();

    void draw();
    void update();

    void translate();
    void rotate();
    void scale();

    void setPosition(const glm::vec3& pos);

    void setAspectRatio(float ration);
    const GLfloat* getCameraMat();

private:

    std::unique_ptr<FlyCamera> camera;

};

#endif /* __SCENE_CAMERA_HPP__ */
