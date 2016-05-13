// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DemoApp::DemoApp(int argc, char* argv[]) : OpenGLApplication(argc, argv),
    cube(nullptr),
    camera(new FlyCamera()),
    keysPressStatus(), 
    currDrawTimeP(0.f),
    prevDrawTimeP(0.f) {

    setSurfaceTitle("DemoApp");
    setSurfaceGeometry(600, 400);
    setSurfaceResizable(false);

    setOpenGLVersion(3, 3);
    setOpenGLCoreProfile(true);

    setDataFolder("data");

    camera->setPerspective(45.f, 0.f, 0.1f, 100.f);
    camera->setLocation(0.f, 0.f, -3.f);
    camera->setLookAt(0.f, 0.f, -1.f);
}

DemoApp::~DemoApp() {
}

void DemoApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    keysPressStatus[keyEvent.getKeyCode()] = keyEvent.isPressed();
}

void DemoApp::onMouseEvent(const MouseEvent& mouseEvent) {
    if(mouseEvent.isMoved()) {
        float sensitivity = .2f;
        float xoffset =  sensitivity * mouseEvent.getXOffset();
        float yoffset = -sensitivity * mouseEvent.getYOffset();
        camera->makePitchYawUpdate(yoffset, xoffset);
    }
}

void DemoApp::onResizeEvent(unsigned int width, unsigned int height) {
    float aspect = width / static_cast<float>(height);
    camera->setAspectRatio(aspect);
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
    texSmile.generateMipmaps();
    texSmile.setMagFilter(GL_NEAREST);
    texSmile.setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
    Texture texCoont("images/container.jpg", GL_TEXTURE_2D);
    texCoont.generateMipmaps();
    texCoont.setMagFilter(GL_NEAREST);
    texCoont.setMinFilter(GL_LINEAR_MIPMAP_NEAREST);

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
            angle = 20.0f * i;
        } else {
            angle = 10.f * (i + 1) * getAppRunDuration();
        }
        modelView = glm::rotate(modelView, glm::radians(angle), glm::vec3(1.f, 0.3f, 0.5f));

        cube->getProgram()->setUniformMat4fv("WorldMat", glm::value_ptr(modelView));
        cube->getProgram()->setUniformMat4fv("CameraMat", camera->getProjectMat4f());
        cube->drawAll();
    }
}

void DemoApp::processUserInput() {
    for(auto keyStatus : keysPressStatus) {
        if(!keyStatus.second) {
            // Key not pressed
            continue;
        }
        float moveSpeed = 10.f;
        float tDist = (currDrawTimeP - prevDrawTimeP) * moveSpeed;
        switch(keyStatus.first) {
        case KeyboardCode::R:
            chagePolygonMode();
            break;
        case KeyboardCode::W:
            camera->makeMoveAtDirection(camera->getLookAt(), tDist);
            break;
        case KeyboardCode::S:
            camera->makeMoveAtDirection(camera->getLookAt(), -tDist);
            break;
        case KeyboardCode::A:
            camera->makeMoveAtDirection(camera->getRightVec(), -tDist);
            break;
        case KeyboardCode::D:
            camera->makeMoveAtDirection(camera->getRightVec(), tDist);
            break;
        default:
            // ignore
            break;
        }
    }
}

void DemoApp::chagePolygonMode() {
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

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    prevDrawTimeP = currDrawTimeP;
    currDrawTimeP = getAppRunDuration();
    processUserInput();
    drawAllCubes();
    surfaceSwapBuffers();
}
