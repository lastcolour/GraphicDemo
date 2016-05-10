// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __FLY_CAMERA_HPP__
#define __FLY_CAMERA_HPP__

#include <glm/glm.hpp>
#include <core/Camera.hpp>

class LIB_EXPORT_CONV FlyCamera : public Camera {
public:

	FlyCamera();
	~FlyCamera();

    void setPerspective(float aspect, float ratio, float zNear, float zFar);
    void setAspectRatio(float aspect);
    void setFoV(float fov);
    void setNearPlane(float zNear);
    void setFarPlane(float zFar);
    void setLocation(float x, float y, float z);
    void setLocation(const glm::vec3& location);
    void setLookAt(float x, float y, float z);
    void setLookAt(const glm::vec3& point);
    void setUpVec(float x, float y, float z);
    void setUpVec(const glm::vec3& up);

    float getFarPlane() const;
    float getNearPlane() const;
    float getFoV() const;
    float getAspectRatio() const;

    void makeLookAround(float pitch, float yaw, float roll);
    void makeLookAround(const glm::vec3& v);
    void makeMove(float xVal, float yVal, float distance);
    void makeMove(const glm::vec3& v);
    void makeMoveAtDirection(const glm::vec3& direction, float distance);
    void makeLookAt(float x, float y, float z);
    void makeLookAt(const glm::vec3& point);

    const glm::vec3& getLocation() const;
    const glm::vec3& getLookAt() const;
    const glm::vec3& getUpVec() const;
    const glm::vec3& getRightVec() const;

    const float* getProjectMat4f() const;

protected:

    void reCalcCameraMat() const;
    void reCalcRightVec();

protected:

    mutable bool modified;
    float aspectRatio;
    float fov;
    float zNear;
    float zFar;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 upVec;
    glm::vec3 rightVec;
    mutable glm::mat4 cameraMat;

};

#endif /* __FLY_CAMERA_HPP__ */
