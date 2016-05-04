#include <openGL/VAOPipeline.hpp>

#include <cassert>

template<class T>
class bind_guard {
public:

    typedef typename T::PtrType PtrT;

    bind_guard(PtrT obj) : objPtr(obj) {
        if(objPtr != nullptr) {
            objPtr->bind();
        }
    }
    ~bind_guard() {
        if(objPtr != nullptr) {
            objPtr->unbind();
        }
    }
private:
    bind_guard();
    bind_guard(const bind_guard&);
    bind_guard& operator=(const bind_guard&);

    PtrT objPtr;
};

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
    drawMode(GL_TRIANGLES),
    vertexSize(0),
    texUnit(nullptr),
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
    SAFE_DELETE(texUnit);
    SAFE_DELETE(shaderPrg);
}

void VAOPipeline::setProgram(ShaderProgram* program) {
    assert(program != nullptr && "Setup invalid program");
    assert(program->isValid() == true && "Setup not compiled program");
    shaderPrg = program;
}

void VAOPipeline::setTexture(Texture2d* texture) {
    texUnit = texture;
}

void VAOPipeline::setVertexBuffer(GLsizeiptr size, const GLvoid* buffer, const VertexPacking* packing, GLenum bufferMode) {
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
}

void VAOPipeline::setElementBuffer(GLsizeiptr size, const GLvoid* buffer, GLenum bufferMode) {
    glBindVertexArray(vaoID);
    glGenBuffers(1, &vertexElemBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexElemBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, buffer, bufferMode);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ShaderProgram* VAOPipeline::getProgram() {
    return shaderPrg;
}

Texture2d* VAOPipeline::getTexture() {
    return texUnit;
}

void VAOPipeline::setDrawMode(GLenum mode) {
    drawMode = mode;
}

void VAOPipeline::draw() {
    glBindVertexArray(vaoID);
    bind_guard<Texture2d> tex(texUnit);
    bind_guard<ShaderProgram> prg(shaderPrg); 
    glDrawArrays(drawMode, 0, vertexSize);
    glBindVertexArray(0);
}