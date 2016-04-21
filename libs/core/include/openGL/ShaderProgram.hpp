#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <core/DEFS.hpp>
#include <openGL/openGL.hpp>

class LIB_EXPORT_CONV ShaderProgram {
public:

    ~ShaderProgram();

    void bind();
    void unbind();

    static ShaderProgram* createProgram(const char* vertShader, const char* fragShader);
    static ShaderProgram* createProgram(GLuint vertShaderID, GLuint fragShaderID);
    
private:
    
    static GLuint linkShaders(GLuint vertShaderID, GLuint fragShaderID);

    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);
    ShaderProgram(GLuint progID);
    
private:

    GLuint programID;
};

#endif /* __SHADER_PROGRAM_HPP__ */
