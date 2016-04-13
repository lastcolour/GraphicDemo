// author: Oleksii Zhogan

#include <GL/glew.h>

#include <DemoApp.hpp>


DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
}

DemoApp::~DemoApp() {

}

void DemoApp::onAppStartEvent() {
}

void DemoApp::onGraphicsInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoApp::onResizeEvent(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}
