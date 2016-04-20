// author: Oleksii Zhogan

#include <openGL/ShaderProgram.hpp>
#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

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

Triangle* DemoApp::createTriangle() {
    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f, // Left
         1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, // Right
         0.0f,  1.0f, 0.0f, 
         0.0f,  0.5f, 0.0f, // Top
         0.0f,  0.0f, 1.0f };

    Triangle* triangle = new Triangle(&vertexData[0], sizeof(vertexData));
    triangle->setShaderProgram(ShaderProgram::createProgram("vert.glsl", "frag.glsl"));
    triangle->setDrawMode(GL_TRIANGLES);
    return triangle;
}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    trianglePtr.reset(createTriangle());
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    trianglePtr->draw();
    getSurface()->swapBuffers();
}
