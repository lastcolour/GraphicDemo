#include "EarthPhysic.hpp"

#include <iostream>
#include <cassert>
#include <cmath>

const float MIN_SPEED = 0.05f;

const float GRAVITY = 9.81f;

EarthPhysics::EarthPhysics(PhysicsModel* modelData) :
    Physics(),
    dataPtr(modelData) {
    currSpeed = dataPtr->speed;
    currTime = 0.f;
    currLen = 0.f;
}

EarthPhysics::~EarthPhysics() {
}


const char* EarthPhysics::getInvalidError() const{
    return validError;
}

float EarthPhysics::updateSpeed(float speed) const {
    if (!dataPtr->jump) {
        return 0.f;
    }
    float tVal = speed * dataPtr->lossEnger;
    if (tVal > MIN_SPEED) {
        return tVal;
    }
    return 0.f;
}

bool EarthPhysics::isValid() const {
    assert(dataPtr != nullptr && "Invalid model ptr");
    if (dataPtr->weight <= 0.f) {
        validError = "Negative weight";
        return false;
    }
    if (dataPtr->speed <= 0.f) {
        validError = "Negative speed";
        return false;
    }
    if (dataPtr->angle >= 90.f || dataPtr->angle <= 0.f) {
        validError = "Wrong angle";
        return false;
    }
    return true;
}

void EarthPhysics::reset() {
    currSpeed = dataPtr->speed;
    currTime = 0.f;
    currLen = 0.f;
}

float EarthPhysics::getFlyHeight() const {
    assert(dataPtr != nullptr && "Invalid model ptr");
    float tHeight = dataPtr->speed * dataPtr->speed;
    tHeight *= sin(dataPtr->angle) * sin(dataPtr->angle);
    tHeight /= 2.f * GRAVITY;
    return tHeight;
}


Point2d EarthPhysics::getPointLoc(float timeP) {
    assert(dataPtr != nullptr && "Invalid model ptr");

    float tTime = timeP - currTime;
    Point2d tPoint(0.f, 0.f);
    tPoint.x = currLen + tTime * currSpeed * cos(dataPtr->angle);
    tPoint.y = tTime * currSpeed * sin(dataPtr->angle) - 0.5f * GRAVITY * tTime * tTime;
    if (tPoint.y <= 0.f) {
        currSpeed = updateSpeed(currSpeed);
        if (currSpeed > 0.f) {
            currTime = timeP;
            currLen = tPoint.x;
        }
        return Point2d(tPoint.x, 0.f);
    }
    return tPoint;
}

float EarthPhysics::getFlyLen() const {
    assert(dataPtr != nullptr && "Invalid model ptr");
    float tSpeed = dataPtr->speed;
    float tResLen = 0.f;
    while (tSpeed > 0.f) {
        float tLen = tSpeed * tSpeed;
        tLen *= sin(2.f * dataPtr->angle);
        tLen /= GRAVITY;
        tResLen += tLen;
        tSpeed = updateSpeed(tSpeed);
    }
    return tResLen;
}