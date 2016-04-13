#ifndef __GLFW_DATA_HANDLER_HPP__
#define __GLFW_DATA_HANDLER_HPP__

#include <core\SurfaceDefs.hpp>

#include <string>

class GLFWDataHandler {
public:

    GLFWDataHandler();
    ~GLFWDataHandler();

    void setColorMode(SurfaceColorMode mode);
    void setBufferMode(SurfaceBufferMode mode);

    void setOpenGLContexVersion(unsigned int major, unsigned int minor);
    void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);
    void setTitle(const std::string& title);
    int getOpenGLContexMajorVersion();
    int getOpenGLContexMinorVersion();

private:

    std::string title;
    unsigned int posX;
    unsigned int posY;
    unsigned int width;
    unsigned int height;
    int glContexMajorVersion;
    int glContexMinorVersion;
    
};

#endif /* __GLFW_DATA_HANDLER_HPP__ */