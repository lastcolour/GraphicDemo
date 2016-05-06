#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <core/DEFS.hpp>

class LIB_EXPORT_CONV Camera {
public:

    Camera() {}
    virtual ~Camera() {}

    virtual void setMoveSpeed() = 0;
    virtual void setMouseSpeed() = 0;

};

#endif /* __CAMERA_HPP__ */