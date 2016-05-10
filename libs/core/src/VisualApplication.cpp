#include <core/VisualApplication.hpp>

VisualApplication::VisualApplication() {
}

VisualApplication::~VisualApplication() {
}

void VisualApplication::appResizeRequest(unsigned int width, unsigned int heigth) {
    onResizeEvent(width, heigth);
}

void VisualApplication::appKeyboardRequest(const KeyboardEvent& keyEvent) {
    onKeyboardEvent(keyEvent);
}

void VisualApplication::appDrawRequest() {
    onDrawEvent();
}

void VisualApplication::appMouseRequest(const MouseEvent& mouseE) {
    onMouseEvent(mouseE);
}

void VisualApplication::appInitRequest() {
    onInitEvent();
}