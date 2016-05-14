#include <LightingApp.hpp>

#include <openGL/VertexBuffer.hpp>

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
    tVaoPtr->setVertexBuffer(VertexBuffer::createCube(0.5f, glm::vec3(0)));
    tVaoPtr->setProgram(new ShaderProgram("shaders/cubeVert.glsl", "shaders/cubetFrag.glsl"));
    return tVaoPtr;
}

VAOPipeline* LightingApp::createLightPoint() {
    VAOPipeline* tVaoPtr = new VAOPipeline();
    tVaoPtr->setVertexBuffer(VertexBuffer::createCube(0.5f, glm::vec3(0)));
    tVaoPtr->setProgram(new ShaderProgram("shaders/lightVert.glsl", "shaders/lightFrag.glsl"));
    return tVaoPtr;
}

void LightingApp::onInitEvent() {
    glClearColor(1.f, 0.f, 0.f, 1.f);
    lightPoint.reset(createLightPoint());
    cube.reset(createCube());
}

void LightingApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);
    lightPoint->drawAll();
    cube->drawAll();
    surfaceSwapBuffers();
}
