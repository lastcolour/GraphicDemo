// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <core/DEFS.hpp>
#include <glm/glm.hpp>

class LIB_EXPORT_CONV Camera {

public:

    // TODO: Remove all dependecies from GLM here

    Camera() {}
    virtual ~Camera() {}

    virtual void setPerspective(float aspect, float ratio, float zNear, float zFar) = 0;
    virtual void setAspectRatio(float aspect) = 0;
    virtual void setFoV(float fov) = 0;
    virtual void setNearPlane(float zNear) = 0;
    virtual void setFarPlane(float zFar) = 0;
    virtual void setLocation(float x, float y, float z) = 0;
    virtual void setLocation(const glm::vec3& location) = 0;
    virtual void setLookAt(float x, float y, float z) = 0;
    virtual void setLookAt(const glm::vec3& point) = 0;
    virtual void setUpVec(float x, float y, float z) = 0;
    virtual void setUpVec(const glm::vec3& up) = 0;

    virtual float getFarPlane() const = 0;
    virtual float getNearPlane() const = 0;
    virtual float getFoV() const = 0;
    virtual float getAspectRatio() const = 0;

    virtual void makeLookAround(float pitch, float yaw, float roll) = 0;
    virtual void makeLookAround(const glm::vec3& v) = 0;
    virtual void makeMove(float xVal, float yVal, float zVal) = 0;
    virtual void makeMove(const glm::vec3& v) = 0;
    virtual void makeMoveAtDirection(const glm::vec3& direction, float distance) = 0;
    virtual void makeLookAt(float x, float y, float z) = 0;
    virtual void makeLookAt(const glm::vec3& point) = 0;

    virtual const glm::vec3& getLocation() const = 0;
    virtual const glm::vec3& getLookAt() const = 0;
    virtual const glm::vec3& getUpVec() const = 0;
    virtual const glm::vec3& getRightVec() const = 0;

    virtual const float* getProjectMat4f() const = 0;
};

#endif /* __CAMERA_HPP__ */
