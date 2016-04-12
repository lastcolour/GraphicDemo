#ifndef __GL_MANAGER_HPP__
#define __GL_MANAGER_HPP__

#include <core\DEFS.hpp>

class LIB_EXPORT_CONV GLManager {
public:

    GLManager();
    virtual ~GLManager();

    virtual bool initialize() = 0;
};

#endif /*__GL_MANAGER_HPP__ */