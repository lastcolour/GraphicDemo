#include <core/ResouceManager.hpp>

std::string getDirPath(const std::string& filePath) {
    size_t lastSlashLoc = 0;
    lastSlashLoc = filePath.find_last_of("\\/");
    return filePath.substr(0, lastSlashLoc);
}

ResourceManager::ResourceManager(const std::string& appLocation) : 
    resourceRoot(getDirPath(appLocation)),
    shadersRoot() {
}

void ResourceManager::setShadersDir(const std::string& dirPath) {
    shadersRoot = dirPath;
}

ResourceManager::~ResourceManager() {
}

std::string ResourceManager::getShaderPath(const std::string& shaderName) const {
    std::string tmpPrefixPath = resourceRoot;
    if(shadersRoot != "") {
        tmpPrefixPath += "/" + shadersRoot;
    }
    return tmpPrefixPath + "/" + shaderName;
}