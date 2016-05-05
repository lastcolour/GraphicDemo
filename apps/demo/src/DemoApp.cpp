// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : OpenGLApplication(argc, argv) {
    setSurfaceTitle("DemoApp");
    setSurfaceGeometry(600, 400);
    setSurfaceResizable(false);

    setOpenGLVersion(3, 3);
    setOpenGLCoreProfile(true);

    setDataFolder("data");
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
    GLfloat vertexData[] = { // array of { <VertCoord, VertColor, TexCoord> }
        -0.5f, -0.5f, 0.0f,
         1.0f,  1.0f, 0.0f,
         0.0f,  0.0f,

         0.5f, -0.5f, 0.0f,
         0.0f,  1.0f, 0.0f,
         1.0f,  0.0f,

         0.5f,  0.5f, 0.0f,
         0.0f,  0.0f, 1.0f,
         1.0f,  1.0f,

        -0.5f,  0.5f, 0.0f,
         1.0f,  0.0f, 0.0f,
         0.0f,  1.0f,
    };
    GLuint elemData[] = {
        0, 1, 2, 2, 3, 0
    };
    VertexPacking packing[] = {
        VertexPacking::VEC3, VertexPacking::VEC3, VertexPacking::VEC2, VertexPacking::NONE
    };

    Texture *texContainer = new Texture("images/container.jpg", GL_TEXTURE_2D, GL_RGB);
    texContainer->setMinFilter(GL_LINEAR);
    texContainer->setMagFilter(GL_NEAREST);

    ShaderProgram tProgram("shaders/vert.glsl", "shaders/frag.glsl");
    tProgram.setUniformTex("Container", texContainer);

    triangle.reset(new VAOPipeline());
    triangle->setProgram(std::move(tProgram));
    triangle->setVertexBuffer(sizeof(vertexData), vertexData, packing);
    triangle->setElementBuffer(sizeof(elemData), elemData);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 transform;
    transform = glm::rotate(transform, glm::pi<float>()/4.f, glm::vec3(0.f, 0.f, 1.f));
    triangle->getProgram()->setUniformMat4fv("transform", glm::value_ptr(transform));

    triangle->drawAllElements();
    surfaceSwapBuffers();
}
