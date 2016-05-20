#include <LightingApp.hpp>

#include <core/FlyCamera.hpp>

#include <LightPoint.hpp>
#include <Cube.hpp>

#include <vector>

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv),
    scenePtr(nullptr) {

    setSurfaceTitle("LightingApp");
    setSurfaceResizable(true);
    setSurfaceGeometry(600, 400);

    setOpenGLCoreProfile(true);
    setOpenGLVersion(3, 3);

    setDataFolder("LightingApp_data"); // TODO: Move this data to some config
}

LightingApp::~LightingApp() {
}

void LightingApp::initScene() {
    scenePtr.reset(new GraphicsScene());

    scenePtr->setBackgroudColor(0.f, 0.f, 0.f, 1.f);

    //scenePtr->add(new LightPoint("shaders/lightVert.glsl", "shaders/lightFrag.glsl"), glm::vec3(0, 0, 0));
    //scenePtr->add(new Cube("shaders/cubeVert.glsl", "shaders/cubeFrag.glsl"), glm::vec3(2, 3, 4));
}

void LightingApp::onMouseEvent(const MouseEvent& mouseE) {
    ioController->controll(mouseE);
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyE) {
    if(keyE.isPressed() && keyE.getKeyCode() == KeyboardCode::ESC) {
        setAppShouldEnd();
    } else {
        ioController->controll(keyE);
    }
}

void LightingApp::drawFrame() {
    scenePtr->update(getAppRunDuration());
    scenePtr->render();
    surfaceSwapBuffers();
}

void LightingApp::mainLoop() {
    initScene();
    while (isAppRunning())
    {
        drawFrame();
    }
}