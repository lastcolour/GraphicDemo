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
    projection(1.0) {
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
    modified = true;
    this->zNear = zNear;
}

void FlyCamera::setFarPlane(float zFar) {
    modified = true;
    this->zFar = zFar;
}

void FlyCamera::setLocation(float x, float y, float z) {
    modified = true;
    position.x = x;
    position.y = y;
    position.z = z;
}

void FlyCamera::setUpVec(float x, float y, float z) {
    modified = true;
    upVec.x = x;
    upVec.y = y;
    upVec.z = z;
}

void FlyCamera::setUpVec(const glm::vec3& up) {
    modified = true;
    upVec = up;
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

void FlyCamera::makeMove(float xVal, float yVal, float zVal) {
    modified = true;
    position.x += xVal;
    position.y += yVal;
    position.z += zVal;
    std::cout << "[FlyCamera] Position: (x=" << position.x << ", y=" << position.y << ", z=" << position.z << ")" << std::endl;
}

void FlyCamera::makeMove(const glm::vec3& v) {
    modified = true;
    position += v;
}

void FlyCamera::makeLookAt(float x, float y, float z) {
    modified = true;
    lookAt.x = x;
    lookAt.y = y;
    lookAt.z = z;
}

void FlyCamera::makeLookAt(const glm::vec3& point) {
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

void FlyCamera::calcProjectMat() const {
    glm::mat4 tPerspMat = glm::perspective(fov, aspectRatio, zNear, zFar);
    glm::mat4 tLookMat = glm::lookAt(position, position - lookAt, upVec);
    projection = tPerspMat * tLookMat;
}

const float* FlyCamera::getProjectMat4f() const {
    if(modified) {
        calcProjectMat();
        modified = false;
    }
    return glm::value_ptr(projection);
}
