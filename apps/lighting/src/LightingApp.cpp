#include <LightingApp.hpp>

#include <core/FlyCamera.hpp>
#include <vector>

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv),
    ioController(new IOCameraController()) {

    ioController->setCamera(new FlyCamera());
    initSurface();

    setDataFolder("LightingApp_data"); // TODO: Move this data to some config
}

void LightingApp::initSurface() {
    setSurfaceTitle("LightingApp");
    setSurfaceResizable(true);
    setSurfaceGeometry(600, 400);

    setOpenGLCoreProfile(true);
    setOpenGLVersion(3, 3);

    glClearColor(0.f, 0.f, 0.f, 1.f);
}

LightingApp::~LightingApp() {
}

void LightingApp::initGeomtry() {
    lightCube.reset(new LightCube("shaders/lightVert.glsl", "shaders/lightFrag.glsl"));
    targetCube.reset(new TargetCube("shaders/cubeVert.glsl", "shaders/cubeFrag.glsl"));
    ioController->addObject(lightCube.get());
    ioController->addObject(targetCube.get());
}

void LightingApp::onMouseEvent(const MouseEvent& mouseE) {
    ioController->controll(mouseE);
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyE) {
    ioController->controll(keyE);
}

void LightingApp::drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT);

    ioController->updateObj(getAppRunDuration());

    lightCube->render();
    targetCube->render();

    surfaceSwapBuffers();
}

void LightingApp::mainLoop() {
    initGeomtry();
    while (isAppRunning())
    {
        drawFrame();
    }
}