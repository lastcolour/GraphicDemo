#include <core/MouseEvent.hpp>

MouseEvent::MouseEvent(float xPos, float yPos, MouseKeyCode keyCode, EventType eventType) : 
    code(keyCode),
    type(eventType),
    x(xPos),
    y(yPos) {
}

MouseEvent::MouseEvent(const MouseEvent& mouseEvent) :
    code(mouseEvent.code),
    type(mouseEvent.type),
    x(mouseEvent.x),
    y(mouseEvent.y) {
}

MouseEvent& MouseEvent::operator=(const MouseEvent& mouseEvent) {
    if(this == &mouseEvent) {
        return *this;
    }
    code = mouseEvent.code;
    type = mouseEvent.type;
    x = mouseEvent.x;
    y = mouseEvent.x;
    return *this;
}


MouseEvent::~MouseEvent() {}

MouseKeyCode MouseEvent::getKeyCode() const { 
    return code;
}

EventType MouseEvent::getType() const {
    return type;
}

float MouseEvent::getX() const { 
    return x;
}

float MouseEvent::getXOffset() const {
    return x;
}

float MouseEvent::getYOffset() const {
    return y;
}

float MouseEvent::getY() const { 
    return y;
}

bool MouseEvent::isPressed() const {
    return type == EventType::PRESSED;
}

bool MouseEvent::isMoved() const { 
    return type == EventType::MOVE;
}