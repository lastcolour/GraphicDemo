// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __FLY_CAMERA_HPP__
#define __FLY_CAMERA_HPP__

#include <graphics/SceneCamera.hpp>


class LIB_EXPORT_CONV SceneFlyCamera : public SceneCamera {
public:

    SceneFlyCamera();
	virtual ~SceneFlyCamera();

    void setPerspective(float aspect, float ratio, float zNear, float zFar);
    void setAspectRatio(float aspect);
    void setFoV(float fov);
    void setNearPlane(float zNear);
    void setFarPlane(float zFar);
    void setLookAt(const glm::vec3& point);
    void setUpVec(const glm::vec3& up);

    float getFarPlane() const;
    float getNearPlane() const;
    float getFoV() const;
    float getAspectRatio() const;
    const glm::vec3& getLookAt() const;
    const glm::vec3& getUpVec() const;
    const glm::vec3& getRightVec() const;

    const GLfloat* getMatrixPtr() const;
    const glm::mat4& getMatrix() const;

    void update();
    void render();

    void makePitchYawUpdate(float pitch, float yaw);
    void makeMoveAtDirection(const glm::vec3& direction, float distance);

protected:

    void reCalcCameraMat() const;
    void reCalcRightVec();

protected:

    mutable bool modified;
    float aspectRatio;
    float fov;
    float zNear;
    float zFar;
    float pitch;
    float yaw;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 upVec;
    glm::vec3 rightVec;
    mutable glm::mat4 cameraMat;

};

#endif /* __FLY_CAMERA_HPP__ */
