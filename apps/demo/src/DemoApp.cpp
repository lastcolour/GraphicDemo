// author: Oleksii Zhogan

#include <openGL/ShaderProgram.hpp>
#include <core/ResouceManager.hpp>
#include <DemoApp.hpp>

#include <string>
#include <iostream>
#include <vector>

DemoApp::DemoApp(int argc, char* argv[]) : OpenGLApplication(argc, argv) {
    setSurfaceTitle("DemoApp");
    setSurfaceGeometry(600, 400);
    setSurfaceResizable(false);

    setOpenGLVersion(3, 3);
    setOpenGLCoreProfile(true);

    setResourceShadersDir("shaders");
}

DemoApp::~DemoApp() {

    glDeleteVertexArrays(1, &trinanglID);
}

GLuint DemoApp::createTriangle() {
    GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f, // Left
         1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, // Right
         1.0f,  1.0f, 1.0f, 
         0.0f,  0.5f, 0.0f, // Top
         0.0f,  0.0f, 1.0f 
    };

    GLuint arrayID;
    GLuint bufferID;
    GLuint elemID;

    GLuint elemData[] = {0, 1, 2};

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &arrayID);
    glBindVertexArray(arrayID);

    glGenBuffers(1, &elemID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elemData), elemData, GL_STATIC_DRAW);
    

    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUF_STRIDE(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUF_STRIDE(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return arrayID;
}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    trinanglID = createTriangle();
    programPtr.reset(new ShaderProgram(loadOpenGLProgram("vert.glsl", "frag.glsl")));
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(trinanglID);
    programPtr->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    programPtr->unbind();
    glBindVertexArray(0);

    surfaceSwapBuffers();
}
