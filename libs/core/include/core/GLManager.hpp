#ifndef __GL_MANAGER_HPP__
#define __GL_MANAGER_HPP__

class GLManager {
public:

    GLManager();
    virtual ~GLManager();

    virtual bool initialize() = 0;
};

#endif /*__GL_MANAGER_HPP__ */