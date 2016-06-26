// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#ifndef __EARTH_PHYSICS_HPP__
#define __EARTH_PHYSICS_HPP__

#include "Physics.hpp"

class DLL_IMPORT EarthPhysics : public Physics {
public:

    EarthPhysics(PhysicsModel* modelData);
    virtual ~EarthPhysics();

    bool isValid() const;
    void reset();
    bool isFinished() const;

    float getFlyLen() const;
    float getFlyHeight() const;
    Point2d getPointLoc(float timeP);

private:

    float updateSpeed(float speed) const;

private:

    PhysicsModel* dataPtr;
    float currSpeed;
    float currLen;
    float currTime;
    float currHeight;
};

#endif /* __EARTH_PHYSICS_HPP__ */
