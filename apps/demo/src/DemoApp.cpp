// author: Oleksii Zhogan

#include <openGL/ShaderProgram.hpp>

#include <DemoApp.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
    Surface* surface = getSurface();
    surface->setTitle("DemoApp");
    surface->setGeometry(600, 400);
    surface->setResizeable(false);
    surface->setOpenGL(3, 3);
    surface->setCoreProfile(true);

    ResourceManager* resources = getResourceManager();
    resources->setShadersDir("shaders");
}

DemoApp::~DemoApp() {

}

void DemoApp::onInitEvent() {
    ShaderProgram::createProgram("vert.glsl", "frag.glsl");
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    getSurface()->swapBuffers();
}