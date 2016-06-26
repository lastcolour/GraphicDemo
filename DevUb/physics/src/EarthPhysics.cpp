// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#include "EarthPhysic.hpp"

#include <iostream>
#include <cassert>
#include <cmath>

const float MIN_SPEED = 0.05f;
const float GRAVITY = 9.81f;


EarthPhysics::EarthPhysics(PhysicsModel* modelData) :
    Physics(),
    dataPtr(modelData),
    currSpeed(0.f),
    currTime(0.f),
    currLen(0.f),
    currHeight(0.f) {

    assert(dataPtr != nullptr && "Invalid pointer");
    currSpeed = dataPtr->speed;
    currHeight = dataPtr->height;
}

EarthPhysics::~EarthPhysics() {
}

float EarthPhysics::updateSpeed(float speed) const {
    assert(dataPtr != nullptr && "Invalid pointer");
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
    if(dataPtr == nullptr) {
        return false;
    }
    if(dataPtr->weight <= 0.f) {
        std::cout << "[EarthPhysics:Error] Negative weight: " << dataPtr->weight << std::endl;
        return false;
    }
    if(dataPtr->speed <= 0.f) {
        std::cout << "[EarthPhysics:Error] Negative speed: " << dataPtr->speed << std::endl;
        return false;
    }
    if(dataPtr->angle > 90.f || dataPtr->angle <= 0.f) {
        std::cout << "[EarthPhysics:Error] Angle value not in range (0, 90]: " << dataPtr->angle << std::endl;
        return false;
    }
    if(dataPtr->height < 0.f) {
        std::cout << "[EarthPhysics:Error] Negative height: " << dataPtr->height << std::endl;
        return false;
    }
    if(dataPtr->jump && (dataPtr->lossEnger >= 1.f || dataPtr->lossEnger <= 0.f)) {
        std::cout << "[EarthPhysics:Error] Negative or zero energy loss when jump: " << dataPtr->lossEnger << std::endl;
        return false;
    }
    return true;
}

void EarthPhysics::reset() {
    assert(dataPtr != nullptr && "Invalid pointer");
    currSpeed = dataPtr->speed;
    currHeight = dataPtr->height;
    currTime = 0.f;
    currLen = 0.f;
}

bool EarthPhysics::isFinished() const {
    return currSpeed <= 0.f;
}

float EarthPhysics::getFlyHeight() const {
    assert(dataPtr != nullptr && "Invalid model ptr");
    float tHeight = dataPtr->speed * dataPtr->speed;
    tHeight *= sin(dataPtr->angle) * sin(dataPtr->angle);
    tHeight /= 2.f * GRAVITY;
    tHeight += dataPtr->height;
    return tHeight;
}


Point2d EarthPhysics::getPointLoc(float timeP) {
    assert(dataPtr != nullptr && "Invalid model ptr");

    float tTime = timeP - currTime;
    Point2d tPoint(0.f, 0.f);
    tPoint.x = currLen + tTime * currSpeed * cos(dataPtr->angle);
    tPoint.y = currHeight + tTime * currSpeed * sin(dataPtr->angle) - 0.5f * GRAVITY * tTime * tTime;
    if (tPoint.y <= 0.f) {
        currSpeed = updateSpeed(currSpeed);
        if (currSpeed > 0.f) {
            currTime = timeP;
            currHeight = 0.f;
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

    if(FLOAT_EQ(dataPtr->angle, 90.f)) {
        return 0.f;
    }
    while (tSpeed > 0.f) {
        float tLen = tSpeed * tSpeed;
        tLen *= sin(2.f * dataPtr->angle);
        tLen /= GRAVITY;
        tResLen += tLen;
        tSpeed = updateSpeed(tSpeed);
    }
    return tResLen;
}
