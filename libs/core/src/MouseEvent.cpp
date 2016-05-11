#include <core/MouseEvent.hpp>

MouseEvent::MouseEvent(float xPos, float yPos, MouseKeyCode keyCode, EventType eventType) : 
    code(keyCode),
    type(eventType),
    timePoint(0.f),
    x(xPos),
    y(yPos),
    prevTimePoint(0.f),
    prevX(yPos),
    prevY(yPos) {
}

MouseEvent::MouseEvent(const MouseEvent& mouseEvent) :
    code(mouseEvent.code),
    type(mouseEvent.type),
    timePoint(mouseEvent.timePoint),
    x(mouseEvent.x),
    y(mouseEvent.y),
    prevTimePoint(mouseEvent.prevTimePoint),
    prevX(mouseEvent.prevX),
    prevY(mouseEvent.prevY) {
}

MouseEvent& MouseEvent::operator=(const MouseEvent& mouseEvent) {
    if(this == &mouseEvent) {
        return *this;
    }
    code = mouseEvent.code;
    type = mouseEvent.type;
    timePoint = mouseEvent.timePoint;
    x = mouseEvent.x;
    y = mouseEvent.y;
    prevTimePoint = mouseEvent.prevTimePoint;
    prevX = mouseEvent.prevX;
    prevY = mouseEvent.prevY;
    return *this;
}

MouseEvent::~MouseEvent() {}

MouseKeyCode MouseEvent::getKeyCode() const { 
    return code;
}

EventType MouseEvent::getType() const {
    return type;
}

void MouseEvent::setPrevEvent(const MouseEvent& prevE) {
    prevTimePoint = prevE.timePoint;
    prevX = prevE.x;
    prevY = prevE.y;
}

void MouseEvent::setTime(float timeP) {
    timePoint = timeP;
}

float MouseEvent::getX() const {
    return x;
}

float MouseEvent::getY() const { 
    return y;
}

float MouseEvent::getXOffset() const {
    return x - prevX;
}

float MouseEvent::getYOffset() const {
    return y - prevY;
}

bool MouseEvent::isPressed() const {
    return type == EventType::PRESSED;
}

bool MouseEvent::isMoved() const { 
    return type == EventType::MOVE;
}