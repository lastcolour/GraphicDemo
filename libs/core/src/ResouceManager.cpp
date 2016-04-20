#include <core/ResouceManager.hpp>

#include <string>

struct PathDataHolder
{
    std::string resourceRoot;
    std::string shaderRoot;
};

const std::string getDirPath(const std::string& filePath) {
    size_t lastSlashLoc = 0;
    lastSlashLoc = filePath.find_last_of("\\/");
    return filePath.substr(0, lastSlashLoc);
}

ResourceManager::ResourceManager(const char* appLocation) : 
    paths(new PathDataHolder()) {
    paths->resourceRoot = getDirPath(appLocation);
    paths->shaderRoot = paths->resourceRoot;
}

ResourceManager::~ResourceManager() {
    SAFE_DELETE(paths);
}

void ResourceManager::setShadersDir(const char* dirPath) {
    paths->shaderRoot = paths->resourceRoot + "/" + dirPath;
}

const char* ResourceManager::getShadersDir() const {
    return paths->shaderRoot.c_str();
}