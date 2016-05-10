#ifndef __MOUSE_EVENT_HPP__
#define __MOUSE_EVENT_HPP__

#include <core/IOEvent.hpp>

#include <assert.h>

class Surface;

enum class MouseKeyCode {
    LEFT,
    RIGHT,
    MID,
    UNKNOWN,
    NONE
};

class LIB_EXPORT_CONV MouseEvent {
public:

    MouseEvent(float xPos, float yPos, MouseKeyCode keyCode, EventType eventType);

    MouseEvent(const MouseEvent& mouseEvent);
    MouseEvent& operator=(const MouseEvent& mouseEvent);

    ~MouseEvent();

    MouseKeyCode getKeyCode() const;
    EventType getType() const;

    float getX() const;
    float getY() const;
    float getXOffset() const;
    float getYOffset() const;

    bool isMoved() const;
    bool isPressed() const;

private:

    MouseKeyCode code;
    EventType type;
    float x;
    float y;
};

#endif /* __MOUSE_EVENT_HPP__ */
