// author: Oleksii Zhogan

#include <GL\glew.h>
#include <GL\GL.h>

#include <DemoApp.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
}

DemoApp::~DemoApp() {
}
    
void DemoApp::onInitializeEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoApp::onResizeEvent() {
    glViewport(0, 0, 100, 100);
    glClear(GL_COLOR_BUFFER_BIT);
}
