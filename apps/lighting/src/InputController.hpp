#ifndef __INPUT_CONTROLLER_HPP__
#define __INPUT_CONTROLLER_HPP__

#include <core/MouseEvent.hpp>
#include <core/KeyboardEvent.hpp>

#include <graphics/Scene3D.hpp>

#include <map>


class InputController {
public:
    
    InputController();
    virtual ~InputController();

    void setSceneToControll(Scene3D* scene);
    void setMouseSensetive(float value);
    void setMoveSpeed(float value);

    void controll(const KeyboardEvent& inpEvent);
    void controll(const MouseEvent& inpEvent);

    void process(float deltaTime);

private:

    std::map<KeyboardCode, bool> keysPressStatus;
    Scene3D* scenePtr;
    float mouseSensetive;
    float moveSpeed;
};

#endif /* __INPUT_CONTROLLER_HPP__ */
