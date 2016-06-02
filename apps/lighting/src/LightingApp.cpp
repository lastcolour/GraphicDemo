#include <LightingApp.hpp>

#include <Cube.hpp>
#include <Light.hpp>
#include <SceneCamera.hpp>

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
    //inpController->setListener(tScene);
    scenePtr.reset(createScene());

    currDrawTimeP = getAppRunDuration();
    prevDrawTimeP = currDrawTimeP;

    while (isAppRunning())
    {
        if (false /* inpController->hasExitEvent() */) {
            // setAppShouldEnd(true);
        } else {
            prevDrawTimeP = currDrawTimeP;
            currDrawTimeP = getAppRunDuration();
            inpController->process(currDrawTimeP - prevDrawTimeP);

            scenePtr->update();
            scenePtr->draw();

            surfaceSwapBuffers();
        }
    }
}

Scene* LightingApp::createScene() {
    Scene* tScene = new Scene();

    tScene->setCameraOwner(new SceneCamera(), glm::vec3(-1));
    tScene->addElement(new Cube(), glm::vec3(0));
    tScene->addElement(new Light(), glm::vec3(1));

    return tScene;
}

void LightingApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    inpController->controll(keyEvent);
}

void LightingApp::onMouseEvent(const MouseEvent& mouseEvent) {
    inpController->controll(mouseEvent);
}

void LightingApp::onResizeEvent(unsigned int width, unsigned int heigth) {
    if (scenePtr != nullptr) { // TODO: Need remove this;
        scenePtr->setViewPort(0, 0, width, heigth);
    }
}