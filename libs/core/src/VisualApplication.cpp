// author: Oleksii Zhogan (alexzhogan@gmail.com)

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

void VisualApplication::appReDrawRequest() {
    onReDrawEvent();
}

void VisualApplication::appMouseRequest(const MouseEvent& mouseE) {
    onMouseEvent(mouseE);
}

void VisualApplication::appInitRequest() {
    onInitEvent();
}