// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <core/DEFS.hpp>
#include <openGL/openGL.hpp>

class LIB_EXPORT_CONV ShaderProgram {
public:

    ShaderProgram(GLuint progID);
    ~ShaderProgram();

    void bind() const;
    void unbind() const;

    GLuint getID() const;

    void setUniform1f(const char* name, float x) const;
    void setUniform4f(const char* name, float x, float y, float z, float w) const;
    
private:
    
    GLint getUniformLocation(const char* name) const;

    void reportUniformNameError(const char* name) const;

    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);
    
private:

    GLuint programID;
};

#endif /* __SHADER_PROGRAM_HPP__ */
