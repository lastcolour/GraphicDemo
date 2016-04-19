// author: Oleksii Zhogan

#include <openGL/ShaderProgram.hpp>
#include <DemoApp.hpp>

#include <string>
#include <iostream>

DemoApp::DemoApp(int argc, char* argv[]) : Application(argc, argv) {
    Surface* surface = getSurface();
    surface->setTitle("DemoApp");
    surface->setGeometry(600, 400);
    surface->setResizeable(false);
    surface->setOpenGL(3, 3);
    surface->setCoreProfile(true);

    ResourceManager* resources = getResourceManager();
    resources->setShadersDir("shaders");
}

DemoApp::~DemoApp() {

}

void DemoApp::onInitEvent() {
    programGL.reset(ShaderProgram::createProgram("vert.glsl", "frag.glsl"));
    if(programGL == nullptr) {
        finishApp(1, "Can't load shaders");
    }
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f, // Left
         1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, // Right
         0.0f,  1.0f, 0.0f, 
         0.0f,  0.5f, 0.0f, // Top
         0.0f,  0.0f, 1.0f
    };

    GLuint bufferID = 0;
    glGenVertexArrays(1, &arrayID);
    glGenBuffers(1, &bufferID);
    glBindVertexArray(arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(arrayID);
    programGL->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    getSurface()->swapBuffers();
}