#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <openGL/openGL.hpp>

#include <string>

class ShaderProgram {
public:

    ShaderProgram(const std::string& vertShader, const std::string& fragShader);
    ~ShaderProgram();

    bool isComplete();

    void bind();
    void unbind();

private:
    GLuint programID;
};

#endif /* __SHADER_PROGRAM_HPP__ */
