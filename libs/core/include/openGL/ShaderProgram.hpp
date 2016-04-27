#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <core/DEFS.hpp>
#include <openGL/openGL.hpp>

class LIB_EXPORT_CONV ShaderProgram {
public:

    ShaderProgram(GLuint progID);
    ~ShaderProgram();

    void bind();
    void unbind();
    
private:
    
    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);
    
private:

    GLuint programID;
};

#endif /* __SHADER_PROGRAM_HPP__ */
