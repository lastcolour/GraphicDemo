#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include "PhysicsModel.hpp"

#include <string>

class DLL_IMPORT Physics {
public:

    Physics() {}
    virtual ~Physics() {}

    virtual void reset() = 0;
    virtual bool isValid() const = 0;
    virtual const char* getInvalidError() const = 0;

    virtual Point2d getPointLoc(float timeP) = 0;
    virtual float   getFlyLen() const = 0;
    virtual float   getFlyHeight() const = 0;
};

#endif /* __PHYSICS_HPP__ */