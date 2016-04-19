#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <core/DEFS.hpp>

#include <openGL/openGL.hpp>

#include <string>
#include <memory>

class LIB_EXPORT_CONV ShaderProgram {
public:

    ~ShaderProgram();

    bool isComplete();

    void bind();
    void unbind();
    
    static std::unique_ptr<ShaderProgram> createProgram(const std::string& vertShader, const std::string& fragShader);
    
private:
    
    ShaderProgram();
    ShaderProgram& operator=(const ShaderProgram&);
    
    ShaderProgram(const std::string& vertShader, const std::string& fragShader);
    
private:
    GLuint programID;
};

#endif /* __SHADER_PROGRAM_HPP__ */
