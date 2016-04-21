#include <core/ResouceManager.hpp>

#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>

std::string getDirPath(const std::string& filePath) {
    size_t lastSlashLoc = 0;
    lastSlashLoc = filePath.find_last_of("\\/");
    return filePath.substr(0, lastSlashLoc);
}

std::string getShaderLog(GLuint instanceID) {
    GLint tLogSize = 0;
    glGetShaderiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if(tLogSize <= 1) {
        return "?";
    }
    std::string tLogStr;
    tLogStr.resize(tLogSize);
    glGetShaderInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
    return tLogStr;
}


class PathDataHolder
{
public:

    PathDataHolder(const char* appLocation) : resourceRoot(getDirPath(appLocation)) {
        shaderRoot = resourceRoot;
    }
    ~PathDataHolder() {}

    void setShaderDir(const char* dirPath) {
       shaderRoot = resourceRoot + "/" + dirPath;
    }

    const std::string& getShaderDir() const {
        return shaderRoot;
    }

private:

    std::string resourceRoot;
    std::string shaderRoot;
};


PathDataHolder* ResourceManager::pathsPtr = nullptr;

void ResourceManager::initialize(const char* appLocation) {
    assert(pathsPtr == nullptr && "Already initialized ResouceManager");
    pathsPtr = new PathDataHolder(appLocation);
}

void ResourceManager::deinitialize() {
    SAFE_DELETE(pathsPtr);
}

void ResourceManager::setShadersDir(const char* dirPath) {
    pathsPtr->setShaderDir(dirPath);
}

GLuint ResourceManager::loadShader(const char* shaderPath, GLenum shaderType) {
    std::string tShaderPath = pathsPtr->getShaderDir() + "/" + shaderPath;
    std::string errForStr = "";
    switch(shaderType) {
    case GL_VERTEX_SHADER:
        errForStr = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        errForStr = "fragment";
        break;
    default:
        assert(0 && "[ResourceManager] Invalid shader type");
        return 0;
    }
    std::ifstream fin(tShaderPath);
    if(!fin.is_open()) {
        std::cerr << "[ResourceManager] Can't open "  << errForStr << " shader file: \"" << tShaderPath << "\"" << std::endl;
        return 0;
    }
    std::string shaderStr;
    shaderStr.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    GLuint shaderID = glCreateShader(shaderType);
    const GLchar* vShaderCode = shaderStr.c_str();
    glShaderSource(shaderID, 1, &vShaderCode, nullptr);
    glCompileShader(shaderID);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if(compiled != GL_TRUE) {
        std::cerr << "[ResourceManager] Can't compile " << errForStr << " shader from file: \"" << tShaderPath << "\"";
        std::cerr << "\n[ResourceManager] Problem: " << getShaderLog(shaderID) << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}