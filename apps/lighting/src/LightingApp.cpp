#include <LightingApp.hpp>

#include <core/FlyCamera.hpp>
#include <vector>

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv),
    ioController(new IOCameraController()) {

    ioController->setCamera(new FlyCamera());

    setSurfaceTitle("LightingApp");
    setSurfaceResizable(true);
    setSurfaceGeometry(600, 400);

    setOpenGLCoreProfile(true);
    setOpenGLVersion(3, 3);

    setDataFolder("LightingApp_data"); // TODO: Move this data to some config
}

LightingApp::~LightingApp() {
}

VAOPipeline* LightingApp::createCube() {
    VAOPipeline* tVaoPtr = new VAOPipeline();
    tVaoPtr->setProgram(new ShaderProgram("shaders/cubeVert.glsl", 
                                          "shaders/cubeFrag.glsl"));
    return tVaoPtr;
}

VAOPipeline* LightingApp::createLightPoint() {
    VAOPipeline* tVaoPtr = new VAOPipeline();
    GLfloat vertexs[] = {
        0.1, 0.1, 0.1,
    };
    VertexPacking packing[] = {
        VertexPacking::VEC3, VertexPacking::NONE
    };
    tVaoPtr->setVertexBuffer(sizeof(vertexs), vertexs, packing);
    tVaoPtr->setProgram(new ShaderProgram("shaders/lightVert.glsl", 
                                          "shaders/lightFrag.glsl"));
    return tVaoPtr;
}

void LightingApp::onInitEvent() {
    glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
    lightPoint.reset(createLightPoint());
    cube.reset(createCube());
}

void LightingApp::onMouseEvent(const MouseEvent& mouseE) {
    ioController->controll(mouseE);
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyE) {
    ioController->controll(keyE);
}

void LightingApp::mainLoop() {
    while (isAppRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
