// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <openGL/openGL.hpp>

#include <string>

class ResourceManager {
public:

    ResourceManager(int argc, char* argv[]);
    ~ResourceManager();
    
    void setShadersDir(const char* path);

    GLuint loadShader(const char* vertShaderName, GLenum shaderType) const;
    GLuint loadProgram(const char* vertShaderName, const char* fragShaderName) const;
    GLuint loadProgram(GLuint vertShaderID, GLuint fragShaderID) const;

private:

    ResourceManager(const ResourceManager&);
    ResourceManager& operator=(const ResourceManager&);

    GLuint linkShaders(GLuint vertID, GLuint fragID) const;

private:

    std::string shadersDir;
    std::string resourcesDir;
};

#endif /* __RESOURCE_MANAGER_HPP__ */