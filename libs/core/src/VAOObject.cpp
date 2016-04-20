#include <openGL/VAOObject.hpp>

Drawable::Drawable() :
    vaoID(0), 
    vboID(0),
    drawMode(GL_TRIANGLES),
    programPtr(nullptr) {
}

Drawable::~Drawable() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}

void Drawable::setShaderProgram(ShaderProgram* program) {
    programPtr = program;
}

void Drawable::setDrawMode(GLenum mode) {
    drawMode = mode;
}

void Drawable::draw() {
    //assert(vaoID != 0 && "[Drawable] Empty VAO");
    //assert(programPtr != nullptr && "[Drawable] Can't draw VAO without program");
    
    glBindVertexArray(vaoID);
    programPtr->bind();
    glDrawArrays(drawMode, 0, 3);
    programPtr->unbind();
    glBindVertexArray(0);
}