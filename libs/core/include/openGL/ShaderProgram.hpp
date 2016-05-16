// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <openGL/Texture.hpp>
#include <openGL/Shader.hpp>

class TextureManager;

class LIB_EXPORT_CONV ShaderProgram : public OpenGLObject {
public:

    typedef ShaderProgram* PtrType;

    ShaderProgram(const char* vertShader, const char* fragShader);
    ShaderProgram(GLuint vertID, GLuint fragID);
    ShaderProgram(const Shader& vertShader, const Shader& fragShader);
    ShaderProgram(ShaderProgram&& program);
    ShaderProgram& operator=(ShaderProgram&& program);
    ~ShaderProgram();

    void setUniform1f(const char* name, float x) const;
    void setUniform4f(const char* name, float x, float y, float z, float w) const;
    void setUniformMat4fv(const char* name, const GLfloat* mat4x4Data) const;
    void setUniformTex(const char* name, Texture* texture);
    void setUniformTex(const char* name, Texture&& texture);

protected:

    bool makeIsBoundCheck();
    bool makeCheck();
    bool makeBind();
    bool makeUnbind();
    bool makeFree();

private:

    GLint uniformFindLocation(const char* name) const;
    void uniformReportNameError(const char* name) const;

    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);

private:

    TextureManager* texManager;
};

#endif /* __SHADER_PROGRAM_HPP__ */
