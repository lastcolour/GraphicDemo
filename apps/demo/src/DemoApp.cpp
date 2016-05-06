// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : OpenGLApplication(argc, argv),
    cube(nullptr) {
    setSurfaceTitle("DemoApp");
    setSurfaceGeometry(600, 400);
    setSurfaceResizable(false);

    setOpenGLVersion(3, 4);
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

void DemoApp::onResizeEvent(unsigned int width, unsigned int height) {
    float aspect = width / static_cast<float>(height);
    projectionMatrix = glm::perspective(45.f, aspect, 0.1f, 100.f);
}

VAOPipeline* DemoApp::createCube() {
    GLfloat cubeVertexData[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    VertexPacking packing[] = {
        VertexPacking::VEC3, VertexPacking::VEC2, VertexPacking::NONE
    };

    Texture texSmile("images/awesomeface.png", GL_TEXTURE_2D);
    texSmile.setMagFilter(GL_LINEAR);
    texSmile.setMinFilter(GL_NEAREST);
    Texture texCoont("images/container.jpg", GL_TEXTURE_2D);
    texCoont.setMagFilter(GL_NEAREST);
    texCoont.setMinFilter(GL_NEAREST);

    ShaderProgram tProgram("shaders/vert.glsl", "shaders/frag.glsl");
    tProgram.setUniformTex("Smile", std::move(texSmile));
    tProgram.setUniformTex("Container", std::move(texCoont));

    VAOPipeline* vaoObj = new VAOPipeline();
    vaoObj->setVertexBuffer(sizeof(cubeVertexData), cubeVertexData, packing, GL_DYNAMIC_DRAW);
    vaoObj->setDrawMode(GL_TRIANGLES);
    vaoObj->setProgram(std::move(tProgram));
    return vaoObj;
}

void DemoApp::onInitEvent() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    cube.reset(createCube());
}

void DemoApp::drawAllCubes() {

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    for(size_t i = 0; i < 10; ++i) {
        glm::mat4 modelView;
        cubePositions[i].z -= 3.0f;
        modelView = glm::translate(modelView, cubePositions[i]);
        GLfloat angle = 0;

        if( i == 1 ||  i % 3 != 0) {
            GLfloat angle = 20.0f * i;
        } else {
            angle = 10.f * (i + 1) * getAppRunDuration();
        }
        modelView = glm::rotate(modelView, glm::radians(angle), glm::vec3(1.f, 0.3f, 0.5f));

        cube->getProgram()->setUniformMat4fv("ModelView", glm::value_ptr(modelView));
        cube->getProgram()->setUniformMat4fv("Projection", glm::value_ptr(projectionMatrix));
        cube->drawAll();
    }
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawAllCubes();
    surfaceSwapBuffers();
}
