#ifndef __IO_CAMERA_CONTROLLER_HPP__
#define __IO_CAMERA_CONTROLLER_HPP__

#include <CameraController.hpp>

#include <core/Camera.hpp>
#include <core/MouseEvent.hpp>
#include <core/KeyboardEvent.hpp>

#include <memory>
#include <map>


class IOCameraController : public CameraController {

    //TODO: Move this class to core

public:

    IOCameraController();
    IOCameraController(Camera* camera);
    virtual ~IOCameraController();

    void controll(const MouseEvent& mouseE);
    void controll(const KeyboardEvent& keyE);

    void setCamera(Camera* camera);
    void setMouseSensitive(float value);
    void setMoveSpeed(float value);

    const GLfloat* getCameraMat();

protected:

    void calcCameraPos();

private:

    IOCameraController(const IOCameraController&);
    IOCameraController& operator=(const IOCameraController&);

    std::unique_ptr<Camera> cameraPtr;
    std::map<KeyboardCode, bool> keysStatus;

    float mouseSensitive;
    float moveSpeed;

    float currTimeP;
    float prevTimeP;
};

#endif /* __IO_CAMERA_CONTROLLER_HPP__ */