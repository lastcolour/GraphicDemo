// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <core/Surface.hpp>

VisualApplication* Surface::application = nullptr;

 Surface::Surface(VisualApplication* app) {
     assert(application == nullptr && "Surface already bounded to application");
     assert(app != nullptr && "Invlid application");
     application = app;
 }

 Surface::~Surface() {
 }

void Surface::sendReDrawEvent() {
    application->appReDrawRequest();
}

void Surface::sendKeyboardEvent(const KeyboardEvent& keyEvent) {
    application->appKeyboardRequest(keyEvent);
}

void Surface::sendMouseEvent(const MouseEvent& mouseEvent) {
    application->appMouseRequest(mouseEvent);
}

void Surface::sendResizeEvent(unsigned int w, unsigned int h) {
    application->appResizeRequest(w, h);
}