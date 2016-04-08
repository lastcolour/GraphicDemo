#ifndef __GLEW_MANAGER_HPP__
#define __GLEW_MANAGER_HPP__

#include <core\GLManager.hpp>

class GLEWManager : public GLManager {
public:

    GLEWManager();
    virtual ~GLEWManager();

    bool initialize();
};

#endif /* __GLEW_MANAGER_HPP__ */