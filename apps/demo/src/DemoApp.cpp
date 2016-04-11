// author: Oleksii Zhogan

#include <GL/glew.h>

#include <DemoApp.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
}

DemoApp::~DemoApp() {
}

void DemoApp::onAppStartEvent() {
    Surface* surface = getSurface();
    surface->setTitle("DemoApp");
    surface->setGeometry(0, 0, 600, 400);
    surface->setColorMode(SurfaceColorMode::RGB);
    surface->setBufferMode(SurfaceBufferMode::DOUBLE);
}

void DemoApp::onGraphicsInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    getSurface()->swapBuffers();
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    getSurface()->swapBuffers();
}

void DemoApp::onResizeEvent(unsigned int width, unsigned int height) {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    getSurface()->swapBuffers();
}