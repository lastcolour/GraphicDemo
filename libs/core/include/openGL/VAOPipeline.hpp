#ifndef __VAO_PIPELINE__
#define __VAO_PIPELINE__

#include <openGL/openGL.hpp>

#include <openGL/ShaderProgram.hpp>
#include <openGL/Texture.hpp>

enum class VertexPacking {
    NONE = 0,
    FLOAT,
    VEC2,
    VEC3,
    VEC4
};

class LIB_EXPORT_CONV VAOPipeline {
public:

    VAOPipeline();
    virtual ~VAOPipeline();

    void setDrawMode(GLenum mode);
    void setProgram(ShaderProgram* program);
    void setProgram(ShaderProgram&& program);
    void setVertexBuffer(GLsizeiptr size, const GLvoid* buffer, const VertexPacking* packing, GLenum bufferMode = GL_STATIC_DRAW);
    void setElementBuffer(GLsizeiptr size, const GLvoid* buffer, GLenum bufferType = GL_UNSIGNED_INT, GLenum bufferMode = GL_STATIC_DRAW);

    ShaderProgram* getProgram();
    GLsizei getVertexSize() const;

    void draw(GLsizei count);
    void drawAll();
    void drawElements(GLsizei count);
    void drawAllElements();

private:

    VAOPipeline(const VAOPipeline&);
    VAOPipeline& operator=(const VAOPipeline&);

private:

    // TODO: Maybe need create single class for buffers
    GLuint vaoID;
    GLuint vertexDataBuffer;
    GLuint vertexElemBuffer;
    GLenum elemBufferType;
    GLenum drawMode;
    GLsizei vertexSize;
    GLsizei elemsSize;
    ShaderProgram* shaderPrg;
};

#endif /* __VAO_PIPELINE__ */