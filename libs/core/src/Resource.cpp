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

    const char* fullPath(const char* filename) {
        lastPathReturned.clear();
        lastPathReturned = appLocation + "/" + filename;
        return lastPathReturned.c_str();
    }

private:

    std::string appLocation;
    std::string lastPathReturned;

};


DirPath* Resource::dirPath = nullptr;

void Resource::setResourceDir(const char* appPath) {
    dirPath = new DirPath(appPath);
    std::atexit([](){
        SAFE_DELETE(dirPath);
    });
}

const char* Resource::getFullPath(const char* filename) {
    return dirPath->fullPath(filename);
}

Resource::Resource() {
}

Resource::~Resource() {
}

