#ifndef __VAO_PIPELINE__
#define __VAO_PIPELINE__

#include <openGL/openGL.hpp>

#include <openGL/ShaderProgram.hpp>
#include <openGL/Texture2d.hpp>

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
    void setTexture(Texture2d* texture);
    void setVertexBuffer(GLsizeiptr size, const GLvoid* buffer, const VertexPacking* packing, GLenum bufferMode = GL_STATIC_DRAW);
    void setElementBuffer(GLsizeiptr size, const GLvoid* buffer, GLenum bufferMode = GL_STATIC_DRAW);

    ShaderProgram* getProgram();
    Texture2d* getTexture();
    GLsizei getVertexSize() const;

    void draw();
    void drawElements();

private:

    VAOPipeline(const VAOPipeline&);
    VAOPipeline& operator=(const VAOPipeline&);

private:

    // TODO: Maybe need create single class for buffers
    GLuint vaoID;
    GLuint vertexDataBuffer;
    GLuint vertexElemBuffer;
    GLenum drawMode;
    GLsizei vertexSize;
    Texture2d* texUnit;
    ShaderProgram* shaderPrg;
};

#endif /* __VAO_PIPELINE__ */