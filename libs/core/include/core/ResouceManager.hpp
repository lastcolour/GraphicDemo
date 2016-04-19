#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <core/DEFS.hpp>

struct PathData;

class LIB_EXPORT_CONV ResourceManager {
public:

    ResourceManager(const char* appLocation);
    ~ResourceManager();

    void setShadersDir(const char* dirPath);
    const char* getShadersDir() const;

private:

    PathData* paths;
};

#endif /* __RESOURCE_MANAGER_HPP__ */