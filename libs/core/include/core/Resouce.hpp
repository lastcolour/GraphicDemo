#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include <core/DEFS.hpp>

class DirPath;

class LIB_EXPORT_CONV Resource {
protected:
    
    static const char* getFullPath(const char* filename);

    Resource();
    virtual ~Resource();

private:

    static DirPath* dirPath;
    static void setResourceDir(const char* dirPath);
    static void setClientResourceDir(const char* dirPath);

    friend class OpenGLApplication;

};

#endif /* __RESOURCE_HPP__ */