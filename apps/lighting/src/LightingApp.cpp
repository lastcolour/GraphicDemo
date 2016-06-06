// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <LightingApp.hpp>

#include <Cube.hpp>
#include <Light.hpp>

#include <graphics/SceneFlyCamera.hpp>

#ifndef DATA_FOLDER_LOCATION
#define DATA_FOLDER_LOCATION "LightingAppData"
#endif

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv) {

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
    inpController.reset(new InputController());
    inpController->setMouseSensetive(0.2f);
    inpController->setMoveSpeed(10.f);
    scenePtr.reset(createScene());
    inpController->setSceneToControll(scenePtr.get());

    currDrawTimeP = getAppRunDuration();
    prevDrawTimeP = currDrawTimeP;

    while (isAppRunning())
    {
        prevDrawTimeP = currDrawTimeP;
        currDrawTimeP = getAppRunDuration();
        inpController->process(currDrawTimeP - prevDrawTimeP);

        scenePtr->update();
        scenePtr->render();

        surfaceSwapBuffers();
    }
}

Scene3D* LightingApp::createScene() {
    Scene3D* tScene = new Scene3D();

    tScene->setCamera(new SceneFlyCamera(), glm::vec3(0));
    tScene->setClearColor(0.f, 0.f, 0.f, 1.f);
    tScene->addElement(new Cube(), glm::vec3(0.f));
    tScene->addLight(new Light(), glm::vec3(3.f, 3.f, -5.f));

    return tScene;
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    inpController->controll(keyEvent);
}

void LightingApp::onMouseEvent(const MouseEvent& mouseEvent) {
    inpController->controll(mouseEvent);
}

void LightingApp::onResizeEvent(unsigned int width, unsigned int heigth) {
    if (scenePtr != nullptr) {
        scenePtr->setViewArea(0.f, 0.f, width, heigth);
    }
}