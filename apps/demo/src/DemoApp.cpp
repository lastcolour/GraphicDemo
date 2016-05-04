// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

DemoApp::DemoApp(int argc, char* argv[]) : OpenGLApplication(argc, argv) {
    setSurfaceTitle("DemoApp");
    setSurfaceGeometry(600, 400);
    setSurfaceResizable(false);

    setOpenGLVersion(3, 3);
    setOpenGLCoreProfile(true);
}

DemoApp::~DemoApp() {
}

void DemoApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    if(keyEvent.getType() == KeyType::PRESSED && keyEvent.getCode() == KeyCode::R) {
        GLint currMode[] = {GL_NONE, GL_NONE};
        glGetIntegerv(GL_POLYGON_MODE, currMode);
        GLenum nextMode = GL_NONE; 
        if (currMode[0] == GL_FILL) {
            nextMode = GL_LINE;
        } else if (currMode[0] == GL_LINE) {
            nextMode = GL_FILL;
        } else {
            std::cout << "[DemoApp] Unknown POLYGON_MODEs: " << currMode[0] << ", " << currMode[1] << std::endl; 
            return;
        }
        glPolygonMode(GL_FRONT_AND_BACK, nextMode);
    }
}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  1.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f,
    };
    VertexPacking packing[] = {
        VertexPacking::VEC3, VertexPacking::VEC2, VertexPacking::NONE
    };
    Shader vert("shaders/vert.glsl", GL_VERTEX_SHADER);
    Shader frag("shaders/frag.glsl", GL_FRAGMENT_SHADER); 
    triangle.reset(new VAOPipeline());
    triangle->setProgram(new ShaderProgram(vert, frag));
    triangle->setTexture(new Texture2d("images/wall.jpg"));
    triangle->setVertexBuffer(sizeof(vertexData), vertexData, packing);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    triangle->draw();
    surfaceSwapBuffers();
}
