// author: Oleksii Zhogan

#include <openGL/ShaderProgram.hpp>
#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

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

    glDeleteVertexArrays(1, &trinanglID);
}

GLuint DemoApp::createTriangle() {
    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f, // Left
         1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, // Right
         0.0f,  1.0f, 0.0f, 
         0.0f,  0.5f, 0.0f, // Top
         0.0f,  0.0f, 1.0f };

    GLuint arrayID;
    GLuint bufferID;
    glGenVertexArrays(1, &arrayID);
    glGenBuffers(1, &bufferID);
    glBindVertexArray(arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUF_STRIDE(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUF_STRIDE(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return arrayID;
}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    trinanglID = createTriangle();
    programPtr.reset(ShaderProgram::createProgram("vert.glsl", "frag.glsl"));
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(trinanglID);
    programPtr->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    programPtr->unbind();
    glBindVertexArray(0);

    getSurface()->swapBuffers();
}
