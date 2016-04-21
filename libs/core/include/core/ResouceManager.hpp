#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <openGL/openGL.hpp>

class PathDataHolder;

class LIB_EXPORT_CONV ResourceManager {
public:

    static void initialize(const char* appName);
    static void deinitialize();

    static void setShadersDir(const char* dirPath);
    static void setModelsDir(const char* dirPath);

    static GLuint loadShader(const char* vertShaderName, GLenum shaderType);


private:

    ResourceManager& operator=(ResourceManager&);
    ResourceManager();
    ~ResourceManager();

private:

    static PathDataHolder* pathsPtr;
};

#endif /* __RESOURCE_MANAGER_HPP__ */