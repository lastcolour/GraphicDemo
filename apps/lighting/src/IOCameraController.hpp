#ifndef __IO_CAMERA_CONTROLLER_HPP__
#define __IO_CAMERA_CONTROLLER_HPP__

#include <core/Camera.hpp>
#include <core/MouseEvent.hpp>
#include <core/KeyboardEvent.hpp>

#include <openGL/openGL.hpp>

#include <memory>
#include <chrono>
#include <vector>
#include <map>

#include <LightCube.hpp> // TODO: Remove this;

class IOCameraController {

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

    void addObject(const SceneObject* obj); // TODO: choose better name for this function
    void updateObj(float timeP);  // TODO: choose better name for this function

protected:

    void calcCameraPos();

private:

    IOCameraController(const IOCameraController&);
    IOCameraController& operator=(const IOCameraController&);

    std::unique_ptr<Camera> cameraPtr;
    std::map<KeyboardCode, bool> keysStatus;
    std::vector<const SceneObject*> objList;

    float mouseSensitive;
    float moveSpeed;

    float currTimeP;
    float prevTimeP;
};

#endif /* __IO_CAMERA_CONTROLLER_HPP__ */