// author: Oleksii Zhogan (alexzhogan@gmail.com)

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

    glDeleteVertexArrays(1, &firstTriangle);
    glDeleteVertexArrays(1, &secondTriangle);
}

GLuint DemoApp::createFirstTriangle() {
    GLfloat vertexData[] = {
        -0.5f, 0.5, 0.0f,
        -0.5f, -0.5, 0.0f,
        0.5f, -0.5, 0.0f,
    };

    GLuint arrayID;
    GLuint bufferID;
    GLuint elemID;

    GLuint elemData[] = {0, 1, 2};
    
    glGenVertexArrays(1, &arrayID);
    glBindVertexArray(arrayID);

    glGenBuffers(1, &elemID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elemData), elemData, GL_STATIC_DRAW);
    

    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUF_STRIDE(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return arrayID;
}

GLuint DemoApp::createSecondTriangle() {
        GLfloat vertexData[] = {
        -0.5f, 0.5, 0.0f,
        0.5f, -0.5, 0.0f,
        0.5f, 0.5, 0.0f,
    };

    GLuint arrayID;
    GLuint bufferID;
    GLuint elemID;

    GLuint elemData[] = {0, 1, 2};
    
    glGenVertexArrays(1, &arrayID);
    glBindVertexArray(arrayID);

    glGenBuffers(1, &elemID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elemData), elemData, GL_STATIC_DRAW);
    

    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUF_STRIDE(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return arrayID;
}

void DemoApp::onKeyboardEvent(const KeyboardEvent& keyEvent) {
    if(keyEvent.getType() == KeyType::PRESSED && keyEvent.getCode() == KeyCode::R) {
        GLint currMode[] = {GL_NONE, GL_NONE};
        glGetIntegerv(GL_POLYGON_MODE, currMode);
        GLenum nextMode = GL_NONE; 
        if (currMode[0] == GL_FILL) {
            nextMode = GL_LINE;
        } else if (currMode[0] == GL_LINE) {
            nextMode = GL_FILL;
        } else {
            std::cout << "[DemoApp] Unknown POLYGON_MODEs: " << currMode[0] << ", " << currMode[1] << std::endl; 
            return;
        }
        glPolygonMode(GL_FRONT_AND_BACK, nextMode);
    }
}

void DemoApp::onInitEvent() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    firstTriangle = createFirstTriangle();
    secondTriangle = createSecondTriangle();

    GLuint vertID = loadOpenGLShader("vert.glsl", GL_VERTEX_SHADER);
    GLuint firstFragID = loadOpenGLShader("frag_1.glsl", GL_FRAGMENT_SHADER);
    GLuint secondFragID = loadOpenGLShader("frag_2.glsl", GL_FRAGMENT_SHADER);
    GLuint progID = loadOpenGLProgram(vertID, firstFragID);
    if(progID != 0) {
        firstProgram.reset(new ShaderProgram(progID));
    }
    progID = loadOpenGLProgram(vertID, secondFragID);
    if(progID != 0) {
        secondProgram.reset(new ShaderProgram(progID));
    }
    
    glDeleteShader(vertID);
    glDeleteShader(firstFragID);
    glDeleteShader(secondFragID);
}

void DemoApp::onDrawEvent() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(firstTriangle);

    firstProgram->bind();
    firstProgram->setUniform4f("vColor", 1.0, 1.0, 1.0, 1.0);
    firstProgram->setUniform1f("xOffset", -0.2f);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, BUF_STRIDE(3 * sizeof(GLfloat)));
    firstProgram->unbind();
    glBindVertexArray(0);

    glBindVertexArray(secondTriangle);
    secondProgram->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, BUF_STRIDE(3 * sizeof(GLfloat)));
    secondProgram->unbind();
    glBindVertexArray(0);

    surfaceSwapBuffers();
}
