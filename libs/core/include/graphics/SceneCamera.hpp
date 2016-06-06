// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SCENE_CAMERA_HPP__
#define __SCENE_CAMERA_HPP__

#include <graphics/SceneElement.hpp>

#include <openGL/openGL.hpp>

class LIB_EXPORT_CONV SceneCamera : public SceneElement {
public:

    SceneCamera() : SceneElement() {}
    virtual ~SceneCamera() {}

    virtual void setPerspective(float aspect, float ratio, float zNear, float zFar) = 0;
    virtual void setAspectRatio(float aspect) = 0;
    virtual void setFoV(float fov) = 0;
    virtual void setNearPlane(float zNear) = 0;
    virtual void setFarPlane(float zFar) = 0;
    virtual void setLookAt(const glm::vec3& point) = 0;
    virtual void setUpVec(const glm::vec3& up) = 0;

    virtual float getFarPlane() const = 0;
    virtual float getNearPlane() const = 0;
    virtual float getFoV() const = 0;
    virtual float getAspectRatio() const = 0;
    virtual const glm::vec3& getLookAt() const = 0;
    virtual const glm::vec3& getUpVec() const = 0;
    virtual const glm::vec3& getRightVec() const = 0;

    virtual const GLfloat* getMatrixPtr() const = 0;
    virtual const glm::mat4& getMatrix() const = 0;

    virtual void makePitchYawUpdate(float pitch, float yaw) = 0;
    virtual void makeMoveAtDirection(const glm::vec3& direction, float distance) = 0;

};

#endif /* __SCENE_CAMERA_HPP__ */
