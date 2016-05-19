#include <core/FlyCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const float MAX_PITCH_VAL = 89.9f;

FlyCamera::FlyCamera() :
	Camera(),
    modified(true),
    aspectRatio(1.6f),
    fov(45.f),
    zNear(0.1f),
    zFar(100.f),
    position(0),
    pitch(0.f),
    yaw(-90.f),
    lookAt(0.f, 0.f, -1.f),
    upVec(0.f, 1.f, 0.f),
    rightVec(0.f),
    cameraMat(1.0) {

    reCalcRightVec();
}

FlyCamera::~FlyCamera() {
}

void FlyCamera::setPerspective(float fov, float aspect, float zNear, float zFar) {
    modified = true;
    this->aspectRatio = aspect;
    this->fov = fov;
    this->zNear = zNear;
    this->zFar = zFar;
}

void FlyCamera::setAspectRatio(float aspect) {
    modified = true;
    this->aspectRatio = aspect;
}

void FlyCamera::setFoV(float fov) {
    modified = true;
    this->fov = fov;
}

void FlyCamera::setNearPlane(float zNear) {
    assert(zNear != zFar && "Too small frustrum box");
    modified = true;
    this->zNear = zNear;
}

void FlyCamera::setFarPlane(float zFar) {
    assert(zNear != zFar && "Too small frustrum box");
    modified = true;
    this->zFar = zFar;
}

void FlyCamera::setLocation(float x, float y, float z) {
    modified = true;
    position.x = x;
    position.y = y;
    position.z = z;
}

void FlyCamera::setLookAt(float x, float y, float z) {
    assert((x != 0.f || y != 0.f || z != 0.f) && "Invalid value for LookAt point");
    modified = true;
    lookAt.x = x;
    lookAt.y = y;
    lookAt.z = z;
}

void FlyCamera::setLookAt(const glm::vec3& point) {
    assert(point != glm::vec3(0) && "Invalid value for LookAt point");
    modified = true;
    lookAt = point;
}

void FlyCamera::setUpVec(float x, float y, float z) {
    assert((x != 0.f || y != 0.f || z != 0.f) && "Invalid value for UP vec");
    modified = true;
    upVec.x = x;
    upVec.y = y;
    upVec.z = z;
    reCalcRightVec();
}

void FlyCamera::setUpVec(const glm::vec3& up) {
    assert(up != glm::vec3(0) && "Invalid value for UP vec");
    modified = true;
    upVec = up;
    reCalcRightVec();
}

void FlyCamera::setLocation(const glm::vec3& location) {
    modified = true;
    position = location;
}

float FlyCamera::getFarPlane() const {
    return zFar;
}

float FlyCamera::getNearPlane() const {
    return zNear;
}

float FlyCamera::getFoV() const {
    return fov;
}

float FlyCamera::getAspectRatio() const {
    return aspectRatio;
}

void FlyCamera::makePitchYawUpdate(float pitchVal, float yawVal) {
    modified = true;

    pitch += pitchVal;
    yaw += yawVal;

    if(pitch > MAX_PITCH_VAL) {
        pitch =  MAX_PITCH_VAL;
    }
    if(pitch < -MAX_PITCH_VAL) {
        pitch = -MAX_PITCH_VAL;
    }

    glm::vec3 tNewLookAt;
    tNewLookAt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tNewLookAt.y = sin(glm::radians(pitch));
    tNewLookAt.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    lookAt = glm::normalize(tNewLookAt);

    reCalcRightVec();
}

void FlyCamera::makeMoveAtDirection(const glm::vec3& direction, float distance) {
    modified = true;
    position += glm::normalize(direction) * distance;
}

const glm::vec3& FlyCamera::getLocation() const {
    return position;
}

const glm::vec3& FlyCamera::getLookAt() const {
    return lookAt;
}

const glm::vec3& FlyCamera::getUpVec() const {
    return upVec;
}

const glm::vec3& FlyCamera::getRightVec() const {
    return rightVec;
}

void FlyCamera::reCalcRightVec() {
    rightVec = glm::normalize(glm::cross(lookAt, upVec));
}

void FlyCamera::reCalcCameraMat() const {
    glm::mat4 tPerspMat = glm::perspective(fov, aspectRatio, zNear, zFar);
    glm::mat4 tLookMat = glm::lookAt(position, position + lookAt, upVec);
    cameraMat = tPerspMat * tLookMat;
}

const GLfloat* FlyCamera::getProjectMat4f() const {
    if(modified) {
        reCalcCameraMat();
        modified = false;
    }
    return glm::value_ptr(cameraMat);
}
