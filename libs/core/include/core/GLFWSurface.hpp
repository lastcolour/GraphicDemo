// author: Oleksii Zhogan

#ifndef __GLFW_SURFACE_HPP__
#define __GLFW_SURFACE_HPP__

#include <core/Surface.hpp>

#include <string>

struct GLFWwindow;

class GLFWSurface : public Surface {
public:

	GLFWSurface();
	virtual ~GLFWSurface();

    void setTitle(const char* title);
    void setGeometry(unsigned int width, unsigned int height);
    void setResizeable(bool flag);
    void setOpenGL(unsigned int major, unsigned int minor);
    void setCoreProfile(bool flag);

    void sendInputEvents();

    bool show();
    bool isOpen();
    void close();
    void swapBuffers();

private:

    static bool GLFW_LIB_INITED;
    static bool GLEW_LIB_INITED;

    static bool initGLEW();

private:

    std::string title;
    unsigned int width;
    unsigned int height;
    int openGLMajor;
    int openGLMinor;
    bool resizeable;
    bool corePorfile;

    GLFWwindow* windowHandler;

private:

    friend class Application;
};

#endif /* __GLFW_SURFACE_HPP__ */
