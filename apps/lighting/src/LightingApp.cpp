#include <LightingApp.hpp>

#include <core/FlyCamera.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <openGL/VAOPipeline.hpp>

#ifndef DATA_FOLDER_LOCATION
#define DATA_FOLDER_LOCATION "LightingAppData"
#endif

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv),
    camera(new FlyCamera()) {

    camera->setLocation(0.f, 0.f, -1.f);

    setSurfaceTitle("LightingApp");
    setSurfaceResizable(true);
    setSurfaceGeometry(600, 400);

    setOpenGLCoreProfile(true);
    setOpenGLVersion(3, 3);

    setDataFolder(DATA_FOLDER_LOCATION); // TODO: Remove this
}

LightingApp::~LightingApp() {
}

void LightingApp::mainLoop() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    cubePtr.reset(createCube("shaders/cubeVert.glsl", "shaders/cubeFrag.glsl"));
    lightPtr.reset(createLight("shaders/lightVert.glsl", "shaders/lightFrag.glsl"));

    currDrawTimeP = getAppRunDuration();
    prevDrawTimeP = currDrawTimeP;

    while (isAppRunning())
    {
        prevDrawTimeP = currDrawTimeP;
        currDrawTimeP = getAppRunDuration();
        processUserInput();
        drawFrame();
    }
}

VAOPipeline* LightingApp::createCube(const char* vertShader, const char* fragShader) {
    GLfloat tVertData[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    VertexPacking tPacking[] = { VertexPacking::VEC3, VertexPacking::NONE };
    ShaderProgram tProgram(vertShader, fragShader);
    if (!tProgram.isValid()) {
        return nullptr;
    }
    VAOPipeline* tPipe = new VAOPipeline();
    tPipe->setVertexBuffer(sizeof(tVertData), tVertData, tPacking, GL_DYNAMIC_DRAW);
    tPipe->setProgram(std::move(tProgram));
    return tPipe;
}

void LightingApp::drawCube() {
    cubePtr->getProgram()->setUniformMat4fv("CameraMat", camera->getDataMat4f());
    cubePtr->drawAll();
}

VAOPipeline* LightingApp::createLight(const char* vertShader, const char* fragShader) {
    VAOPipeline* lightPtr = createCube(vertShader, fragShader);
    lightTransform = glm::scale(lightTransform, glm::vec3(.2f, .2f, .2f));
    lightTransform = glm::translate(lightTransform, glm::vec3(4.f, 4.f, 4.f));
    lightPtr->getProgram()->setUniformMat4fv("TransformMat", glm::value_ptr(lightTransform));
    return lightPtr;
}

void LightingApp::drawLight() {
    lightPtr->getProgram()->setUniformMat4fv("CameraMat", camera->getDataMat4f());
    lightPtr->drawAll();
}

void LightingApp::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCube();
    drawLight();
    surfaceSwapBuffers();
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    keysPressStatus[keyEvent.getKeyCode()] = keyEvent.isPressed();
}

void LightingApp::onMouseEvent(const MouseEvent& mouseEvent) {
    if (mouseEvent.isMoved()) {
        float sensitivity = .2f;
        float xoffset =  sensitivity * mouseEvent.getXOffset();
        float yoffset = -sensitivity * mouseEvent.getYOffset();
        camera->makePitchYawUpdate(yoffset, xoffset);
    }
}

void LightingApp::onResizeEvent(unsigned int width, unsigned int heigth) {
    glViewport(0, 0, width, heigth);
    camera->setAspectRatio(width / float(heigth));
}

void LightingApp::processUserInput() {
    for (auto keyStatus : keysPressStatus) {
        if (!keyStatus.second) {
            // Key not pressed
            continue;
        }
        float moveSpeed = 5.f;
        float tDist = (currDrawTimeP - prevDrawTimeP) * moveSpeed;
        switch (keyStatus.first) {
        case KeyboardCode::R:
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