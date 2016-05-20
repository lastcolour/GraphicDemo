#ifndef __CAMERA_CONTROLLER_HPP__
#define __CAMERA_CONTROLLER_HPP__

#include <openGL/openGL.hpp>

class CameraController {
public:

    CameraController() {}
    virtual ~CameraController() {}

    virtual void update(float timeP) = 0;
    virtual const GLfloat* getCameraMat() = 0;

private:

    CameraController(const CameraController&);
    CameraController& operator=(const CameraController&);
};

#endif /* __CAMERA_CONTROLLER_HPP__ */