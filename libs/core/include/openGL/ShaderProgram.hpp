// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <openGL/OpenGLObject.hpp>
#include <openGL/Shader.hpp>

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

protected:

    bool makeIsBoundCheck(GLuint resourceID);
    bool makeCheck(GLuint resourceID);
    bool makeBind(GLuint resourceID);
    bool makeUnbind(GLuint resourceID);
    bool makeFree(GLuint resourceID);

private:

    GLint getUniformLocation(const char* name) const;
    void reportUniformNameError(const char* name) const;

    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);
};

#endif /* __SHADER_PROGRAM_HPP__ */
