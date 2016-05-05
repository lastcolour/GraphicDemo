// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <core/Resouce.hpp>
#include <openGL/openGL.hpp>


class LIB_EXPORT_CONV Shader : public Resource {
public:

    Shader(const char* shaderName, GLenum type);
    Shader(Shader&& shader);
    Shader& operator=(Shader&& shader);
    ~Shader();

    GLuint getID() const; 
    GLenum getType() const; 

    bool isValid() const;

private:

    Shader(const Shader& shader);
    Shader& operator=(const Shader& shader);

    GLuint shaderID;
    GLenum shaderType;
};

#endif /* __SHADER_HPP__ */