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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    inpController.reset(new InputController());
    inpController->setMouseSensetive(0.2f);
    inpController->setMoveSpeed(20.f);
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
    tScene->add(new Cube(), glm::vec3(0));
    tScene->add(new Light(), glm::vec3(1));

    return tScene;
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    inpController->controll(keyEvent);
}

void LightingApp::onMouseEvent(const MouseEvent& mouseEvent) {
    inpController->controll(mouseEvent);
}

void LightingApp::onResizeEvent(unsigned int width, unsigned int heigth) {
    glViewport(0, 0, width, heigth);
    if (scenePtr != nullptr) {
        scenePtr->getCamera()->setAspectRatio(width / float(heigth));
    }
}