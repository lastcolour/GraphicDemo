// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <graphics/SceneFlyCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const float MAX_PITCH_VAL = 89.9f;
const float MIN_NEAR_FAR_DELTA = 0.1f;

SceneFlyCamera::SceneFlyCamera() :
	SceneCamera(),
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

SceneFlyCamera::~SceneFlyCamera() {
}

void SceneFlyCamera::setPerspective(float fov, float aspect, float zNear, float zFar) {
    modified = true;
    this->aspectRatio = aspect;
    this->fov = fov;
    this->zNear = zNear;
    this->zFar = zFar;
}

void SceneFlyCamera::setAspectRatio(float aspect) {
    modified = true;
    this->aspectRatio = aspect;
}

void SceneFlyCamera::setFoV(float fov) {
    modified = true;
    this->fov = fov;
}

void SceneFlyCamera::setNearPlane(float zNear) {
    assert(std::abs(zNear - zFar) >  MIN_NEAR_FAR_DELTA && "Too small frustrum box");
    modified = true;
    this->zNear = zNear;
}

void SceneFlyCamera::setFarPlane(float zFar) {
    assert(std::abs(zNear - zFar) >  MIN_NEAR_FAR_DELTA && "Too small frustrum box");
    modified = true;
    this->zFar = zFar;
}

void SceneFlyCamera::setLookAt(const glm::vec3& point) {
    assert(point != glm::vec3(0) && "Invalid value for LookAt point");
    modified = true;
    lookAt = point;
}

void SceneFlyCamera::setUpVec(const glm::vec3& up) {
    assert(up != glm::vec3(0) && "Invalid value for UP vec");
    modified = true;
    upVec = up;
    reCalcRightVec();
}

float SceneFlyCamera::getFarPlane() const {
    return zFar;
}

float SceneFlyCamera::getNearPlane() const {
    return zNear;
}

float SceneFlyCamera::getFoV() const {
    return fov;
}

float SceneFlyCamera::getAspectRatio() const {
    return aspectRatio;
}

void SceneFlyCamera::makePitchYawUpdate(float pitchVal, float yawVal) {
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

void SceneFlyCamera::makeMoveAtDirection(const glm::vec3& direction, float distance) {
    modified = true;
    getPosition() += glm::normalize(direction) * distance;
}

const glm::vec3& SceneFlyCamera::getLookAt() const {
    return lookAt;
}

const glm::vec3& SceneFlyCamera::getUpVec() const {
    return upVec;
}

const glm::vec3& SceneFlyCamera::getRightVec() const {
    return rightVec;
}

void SceneFlyCamera::reCalcRightVec() {
    rightVec = glm::normalize(glm::cross(lookAt, upVec));
}

void SceneFlyCamera::reCalcCameraMat() const {
    glm::mat4 tPerspMat = glm::perspective(fov, aspectRatio, zNear, zFar);
    glm::mat4 tLookMat = glm::lookAt(getPosition(), getPosition() + lookAt, upVec);
    cameraMat = tPerspMat * tLookMat;
}

const GLfloat* SceneFlyCamera::getMatrixPtr() const {
    return glm::value_ptr(getMatrix());
}
const glm::mat4& SceneFlyCamera::getMatrix() const {
    if (modified) {
        reCalcCameraMat();
        modified = false;
    }
    return cameraMat;
}

void SceneFlyCamera::update() {
}

void SceneFlyCamera::render() {
}
