#include <core/FlyCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

FlyCamera::FlyCamera() :
	Camera(),
    modified(true),
    aspectRatio(1.6f),
    fov(45.f),
    zNear(0.1f),
    zFar(100.f),
    position(0),
    lookAt(0.f, 0.f, 1.f),
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
    assert(x != 0.f && y != 0.f && z != 0.f && "Invalid value for LookAt point");
    lookAt.x = x;
    lookAt.y = y;
    lookAt.z = z;
}

void FlyCamera::setLookAt(const glm::vec3& point) {
    assert(point != glm::vec3(0) && "Invalid value for LookAt point");
    lookAt = point;
}

void FlyCamera::setUpVec(float x, float y, float z) {
    assert(x != 0.f && y != 0.f && z != 0.f && "Invalid value for UP vec");
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

void FlyCamera::makeLookAround(float pitch, float yaw, float roll) {
}

void FlyCamera::makeLookAround(const glm::vec3& v) {
}

void FlyCamera::makeMove(float xVal, float yVal, float zVal) {
    modified = true;
    position.x += xVal;
    position.y += yVal;
    position.z += zVal;
#ifndef GD_CORE_LIB_DEBUG
    std::cout << "[FlyCamera] Position: (x=" << position.x << ", y=" << position.y << ", z=" << position.z << ")" << std::endl;
#endif
}

void FlyCamera::makeMove(const glm::vec3& v) {
    modified = true;
    position += v;
#ifndef GD_CORE_LIB_DEBUG
    std::cout << "[FlyCamera] Position: (x=" << position.x << ", y=" << position.y << ", z=" << position.z << ")" << std::endl;
#endif
}

void FlyCamera::makeMoveAtDirection(const glm::vec3& direction, float distance) {
    modified = true;
    position += glm::normalize(direction) * distance;
#ifndef GD_CORE_LIB_DEBUG
    std::cout << "[FlyCamera] Position: (x=" << position.x << ", y=" << position.y << ", z=" << position.z << ")" << std::endl;
#endif
}

void FlyCamera::makeLookAt(float x, float y, float z) {
    modified = true;
    lookAt.x = x;
    lookAt.y = y;
    lookAt.z = z;
}

void FlyCamera::makeLookAt(const glm::vec3& point) {
    assert(point != position && "Invalid look up points");
    modified = true;
    lookAt = point;
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
    rightVec = glm::normalize(glm::cross(upVec, lookAt));
}

void FlyCamera::reCalcCameraMat() const {
    glm::mat4 tPerspMat = glm::perspective(fov, aspectRatio, zNear, zFar);
    glm::mat4 tLookMat = glm::lookAt(position, position - lookAt, upVec);
    cameraMat = tPerspMat * tLookMat;
}

const float* FlyCamera::getProjectMat4f() const {
    if(modified) {
        reCalcCameraMat();
        modified = false;
    }
    return glm::value_ptr(cameraMat);
}
