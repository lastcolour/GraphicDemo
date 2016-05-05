// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <core/Resouce.hpp>

#include <cassert>
#include <string>

std::string getDirPath(const std::string& filePath) {
    size_t lastSlashLoc = 0;
    lastSlashLoc = filePath.find_last_of("\\/");
    return filePath.substr(0, lastSlashLoc);
}

class DirPath {
public:

    DirPath(const char* dirName) :  
        appLocation(getDirPath(dirName)),
        lastPathReturned("") {
        assert(appLocation != "" && "Invalid application location");
    }

    void setClientPath(const char* path) {
        assert(path != nullptr && "Invalid data path");
        clientPath = path;
    }

    const char* fullPath(const char* filename) {
        lastPathReturned.clear();
        lastPathReturned = appLocation;
        if(clientPath != "") {
            lastPathReturned = lastPathReturned + "/" + clientPath;
        }
        lastPathReturned = lastPathReturned + "/" + filename;
        return lastPathReturned.c_str();
    }

private:

    std::string appLocation;
    std::string clientPath;
    std::string lastPathReturned;

};


DirPath* Resource::dirPath = nullptr;

void Resource::setResourceDir(const char* appPath) {
    dirPath = new DirPath(appPath);
    std::atexit([](){
        SAFE_DELETE(dirPath);
    });
}

void Resource::setClientResourceDir(const char* path) {
    assert(dirPath != nullptr && "Resources not initialized");
    dirPath->setClientPath(path);
}

const char* Resource::getFullPath(const char* filename) {
    assert(dirPath != nullptr && "Resources not initialized");
    return dirPath->fullPath(filename);
}

Resource::Resource() {
}

Resource::~Resource() {
}

