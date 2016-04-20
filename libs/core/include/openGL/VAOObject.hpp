#ifndef __VAO_OBJECT_HPP__
#define __VAO_OBJECT_HPP__

#include <openGL/openGL.hpp>
#include <openGL/ShaderProgram.hpp>

#include <assert.h>


template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
class VAOObject {
public:

    VAOObject(const void* buffer, GLuint size, GLenum firstType=GL_FLOAT, GLenum seconType=GL_FLOAT);
    ~VAOObject();

    void setShaderProgram(ShaderProgram* program);
    void setDrawMode(GLenum mode);

    void draw();

private:

    VAOObject();
    VAOObject& operator=(VAOObject&);

private:

    GLuint vaoID;
    GLuint vboID;
    GLenum drawMode;
    ShaderProgram* programPtr;
};


template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
VAOObject<F_COUNT, F_TYPE, S_COUNT, S_TYPE>::VAOObject(const void* buffer, GLuint size, GLenum firstType/* = GL_FLOAT*/, GLenum secondType/* = GL_FLOAT */) : 
    vaoID(0), 
    vboID(0),
    drawMode(GL_TRIANGLES),
    programPtr(nullptr) {

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

    GLuint packSize = F_COUNT * sizeof(F_TYPE) + S_COUNT * sizeof(S_TYPE);

    glVertexAttribPointer(0, F_COUNT, firstType, GL_FALSE, packSize, (GLvoid*)0);
    glVertexAttribPointer(1, S_COUNT, secondType, GL_FALSE, packSize, (GLvoid*)(F_COUNT * sizeof(F_TYPE)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    std::cout << "[VAO:Draw] " << vaoID;
    std::cout << "\n[VAO:Draw] " << vboID;
    std::cout << "\n[VAO:Draw] " << drawMode;
    std::cout << "\n[VAO:Draw] " << programPtr << std::endl;
};

template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
VAOObject<F_COUNT, F_TYPE, S_COUNT, S_TYPE>::~VAOObject() {
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
}

template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
void VAOObject<F_COUNT, F_TYPE, S_COUNT, S_TYPE>::setShaderProgram(ShaderProgram* program) {
    programPtr = program;
}

template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
void VAOObject<F_COUNT, F_TYPE, S_COUNT, S_TYPE>::setDrawMode(GLenum mode) {
    drawMode = mode;
}

template<GLuint F_COUNT, typename F_TYPE, GLuint S_COUNT, typename S_TYPE>
void VAOObject<F_COUNT, F_TYPE, S_COUNT, S_TYPE>::draw() {
    assert(vaoID != 0 && "[Drawable] Empty VAO");
    assert(programPtr != nullptr && "[Drawable] Can't draw VAO without program");

    glBindVertexArray(vaoID);
    programPtr->bind();
    glDrawArrays(drawMode, 0, 3);
    programPtr->unbind();
    glBindVertexArray(0);
}


#endif /* __VAO_OBJECT_HPP__ */