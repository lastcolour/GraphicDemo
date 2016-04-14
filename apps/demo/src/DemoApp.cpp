// author: Oleksii Zhogan

#include <openGL/openGL.hpp>
#include <core/Surface.hpp>

#include <DemoApp.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
    Surface* surface = getSurface();
    surface->setTitle("DemoApp");
    surface->setGeometry(600, 400);
    surface->setResizeable(false);
    surface->setOpenGL(3, 3);
    surface->setCoreProfile(true);
}

DemoApp::~DemoApp() {

}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void DemoApp::onResizeEvent(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}