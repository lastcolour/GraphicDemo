// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/VAOPipeline.hpp>

#include <utility>
#include <cassert>

struct AttribData {
    GLint compNum;
    GLenum valType;
    GLsizei typeSize;
};

AttribData calcVertexAttribData(VertexPacking pack) {
    AttribData data;
    switch (pack)
    {
    case VertexPacking::FLOAT:
        data.compNum = 1;
        data.valType = GL_FLOAT;
        data.typeSize = sizeof(GLfloat);
        break;
    case VertexPacking::VEC2:
        data.compNum = 2;
        data.valType = GL_FLOAT;
        data.typeSize = sizeof(GLfloat);
        break;
    case VertexPacking::VEC3:
        data.compNum = 3;
        data.valType = GL_FLOAT;
        data.typeSize = sizeof(GLfloat);
        break;
    case VertexPacking::VEC4:
        data.compNum = 4;
        data.valType = GL_FLOAT;
        data.typeSize = sizeof(GLfloat);
        break;
    case VertexPacking::NONE:
    default:
        assert(0 && "Invalid pack value");
        break;
    }
    return data;
}

GLsizei calcVertexStride(const VertexPacking* packing) {
    GLsizei tStride = 0;
    VertexPacking tIter = VertexPacking::NONE;
    while((tIter = *packing++) != VertexPacking::NONE) {
        AttribData tData = calcVertexAttribData(tIter);
        tStride += tData.compNum * tData.typeSize;
    }
    return tStride;
}

VAOPipeline::VAOPipeline() : 
    vaoID(0),
    vertexDataBuffer(0),
    vertexElemBuffer(0),
    elemBufferType(GL_NONE),
    drawMode(GL_TRIANGLES),
    vertexSize(0),
    elemsSize(0),
    shaderPrg(nullptr) {

    glGenVertexArrays(1, &vaoID);
    assert(vaoID != 0 && "Can't generate VAO"); 
}

VAOPipeline::~VAOPipeline() {
    if(vaoID != 0) {
        glDeleteVertexArrays(1, &vaoID);
    }
    if(vertexDataBuffer != 0) {
        glDeleteBuffers(1, &vertexDataBuffer);
    }
    if(vertexElemBuffer != 0) {
        glDeleteBuffers(1, &vertexElemBuffer);
    }
    SAFE_DELETE(shaderPrg);
    CHECK_OPENGL_STATUS("VAOPipeline:~VAOPipeline");
}

void VAOPipeline::setProgram(ShaderProgram* program) {
    assert(program != nullptr && "Setup invalid program");
    assert(program->isValid() == true && "Setup not compiled program");
    program->ref();
    if(shaderPrg != nullptr && shaderPrg->getRefCount() == 0) {
        shaderPrg->unref();
        SAFE_DELETE(shaderPrg);
    }
    shaderPrg = program;
}

void VAOPipeline::setProgram(ShaderProgram&& program) {
    assert(program.isValid() == true && "Setup not compiled program");
    if(shaderPrg != nullptr && shaderPrg->getRefCount() == 0) {
        shaderPrg->unref();
        SAFE_DELETE(shaderPrg);
    }
    shaderPrg = new ShaderProgram(std::move(program));
}

void VAOPipeline::setVertexBuffer(GLsizeiptr size, const GLvoid* buffer, const VertexPacking* packing, GLenum bufferMode) {
    if(vertexDataBuffer != 0) {
        glDeleteBuffers(1, &vertexDataBuffer);
    }
    glBindVertexArray(vaoID);
    glGenBuffers(1, &vertexDataBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexDataBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, buffer, bufferMode);
    GLsizei tStride = calcVertexStride(packing);
    GLsizei tOffset = 0;
    GLuint tCurrIndex = 0;
    vertexSize = static_cast<GLsizei>(size) / tStride;
    assert(size % tStride == 0 && "Vertex buffer has wrong data packing: size != vertex count");
    VertexPacking pIter = packing[0];
    while((pIter = *packing++) != VertexPacking::NONE) {
        AttribData tData = calcVertexAttribData(pIter); 
        glVertexAttribPointer(tCurrIndex, tData.compNum, tData.valType, GL_FALSE, tStride, BUF_STRIDE(tOffset));
        glEnableVertexAttribArray(tCurrIndex);
        tOffset += tData.compNum * tData.typeSize;
        ++tCurrIndex;
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_OPENGL_STATUS("VAOPipeline:setVertexBuffer");
}

void VAOPipeline::setElementBuffer(GLsizeiptr size, const GLvoid* buffer, GLenum bufferType, GLenum bufferMode) {
    if(vertexElemBuffer != 0) {
        glDeleteBuffers(1, &vertexElemBuffer);
    }
    elemBufferType = bufferType;
    switch (bufferType)
    {
    case GL_UNSIGNED_INT:
        elemsSize =  static_cast<GLsizei>(size) / sizeof(GLuint);
        assert(static_cast<GLsizei>(size) % sizeof(GLuint) == 0 && "Element buffer has wrong structure");
        break;
    default:
        assert(0 && "Unknown buffer type");
        break;
    }
    glBindVertexArray(vaoID);
    glGenBuffers(1, &vertexElemBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexElemBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, bufferMode);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    CHECK_OPENGL_STATUS("VAOPipeline:setElementBuffer");
}

ShaderProgram* VAOPipeline::getProgram() {
    return shaderPrg;
}

void VAOPipeline::setDrawMode(GLenum mode) {
    drawMode = mode;
}

void VAOPipeline::drawElements(GLsizei count) {
    assert(vertexElemBuffer != 0 && "Can't draw elements without element buffer");
    if(elemsSize == 0) {
        return;
    }
    glBindVertexArray(vaoID);
    shaderPrg->bind(); 

    glDrawElements(drawMode, count, elemBufferType, 0);

    shaderPrg->unbind();
    glBindVertexArray(0);
    CHECK_OPENGL_STATUS("VAOPipeline:drawElements");
}

void VAOPipeline::drawAllElements() {
    assert(vertexElemBuffer != 0 && "Can't draw elements without element buffer");
    glBindVertexArray(vaoID);
    shaderPrg->bind(); 

    glDrawElements(drawMode, elemsSize, elemBufferType, 0);

    shaderPrg->unbind();
    glBindVertexArray(0);
    CHECK_OPENGL_STATUS("VAOPipeline:drawAllElements");
}

void VAOPipeline::draw(GLsizei count) {
    glBindVertexArray(vaoID);
    shaderPrg->bind(); 

    glDrawArrays(drawMode, 0, count);

    shaderPrg->unbind();
    glBindVertexArray(0);
    CHECK_OPENGL_STATUS("VAOPipeline:draw");
}

void VAOPipeline::drawAll() {
    glBindVertexArray(vaoID);
    shaderPrg->bind(); 

    glDrawArrays(drawMode, 0, vertexSize);

    shaderPrg->unbind();
    glBindVertexArray(0);
    CHECK_OPENGL_STATUS("VAOPipeline:drawAll");
}
