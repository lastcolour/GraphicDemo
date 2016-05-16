#include <LightingApp.hpp>
#include <vector>

LightingApp::LightingApp(int argc, char* argv[]) :
    OpenGLApplication(argc, argv) {

    setSurfaceTitle("LightingApp");
    setSurfaceResizable(true);
    setSurfaceGeometry(600, 400);

    setOpenGLCoreProfile(true);
    setOpenGLVersion(3, 3);
}

LightingApp::~LightingApp() {
}

VAOPipeline* LightingApp::createCube() {
    VAOPipeline* tVaoPtr = new VAOPipeline();
    tVaoPtr->setProgram(new ShaderProgram("shaders/cubeVert.glsl", "shaders/cubetFrag.glsl"));
    return tVaoPtr;
}

VAOPipeline* LightingApp::createLightPoint() {
    VAOPipeline* tVaoPtr = new VAOPipeline();
    GLfloat vertexs[] = {
        -0.5, -0.5f, 0.f,
         0.5, -0.5f, 0.f,
         0.0,  0.5f, 0.f,
    };
    tVaoPtr->setProgram(new ShaderProgram("shaders/lightVert.glsl", "shaders/lightFrag.glsl"));
    return tVaoPtr;
}

void LightingApp::onInitEvent() {
    glClearColor(1.f, 0.f, 0.f, 1.f);
    lightPoint.reset(createLightPoint());
    cube.reset(createCube());
}

void LightingApp::mainLoop() {
}

void LightingApp::onReDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    surfaceSwapBuffers();
}
