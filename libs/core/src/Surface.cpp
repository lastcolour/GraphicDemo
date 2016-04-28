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

void Surface::sendDrawEvent() {
    application->appDrawRequest();
}

void Surface::sendKeyboardEvent(const KeyboardEvent& keyEvent) {
    application->appKeyboardRequest(keyEvent);
}

void Surface::sendMouseEvent() {
}

void Surface::sendResizeEvent(unsigned int width, unsigned int height) {
    application->appResizeRequest(width, height);
}