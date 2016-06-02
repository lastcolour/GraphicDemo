#ifndef __INPUT_CONTROLLER_HPP__
#define __INPUT_CONTROLLER_HPP__

#include <core/MouseEvent.hpp>
#include <core/KeyboardEvent.hpp>

#include <map>

enum class AppEvent {
    MOVE_FORWARD,
    MOVE_BACK,
    MOVE_LEFT,
    MOVE_RIGHT,
    PITCH_UPDATE,
    YAW_UPDATE,
};

class InputController {
public:
    
    InputController();
    virtual ~InputController();

    void setMouseSensetive(float value);

    void controll(const KeyboardEvent& inpEvent);
    void controll(const MouseEvent& inpEvent);

    void process(float deltaTime);

private:

    std::map<KeyboardCode, bool> keysPressStatus;
    float mouseSensetive;
};

#endif /* __INPUT_CONTROLLER_HPP__ */
