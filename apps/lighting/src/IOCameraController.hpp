#ifndef __IO_CAMERA_CONTROLLER_HPP__
#define __IO_CAMERA_CONTROLLER_HPP__

#include <core/Camera.hpp>
#include <core/MouseEvent.hpp>
#include <core/KeyboardEvent.hpp>

#include <memory>
#include <map>

class IOCameraController {
public:

    IOCameraController();
    IOCameraController(Camera* camera);
    virtual ~IOCameraController();

    void controll(const MouseEvent& mouseE);
    void controll(const KeyboardEvent& keyE);

    void setCamera(Camera* camera);

    void* getCameraMat();

private:

    IOCameraController(const IOCameraController&);
    IOCameraController& operator=(const IOCameraController&);

    std::unique_ptr<Camera> cameraPtr;
    std::map<KeyboardCode, KeyboardEvent> keysStatus;
};

#endif /* __IO_CAMERA_CONTROLLER_HPP__ */