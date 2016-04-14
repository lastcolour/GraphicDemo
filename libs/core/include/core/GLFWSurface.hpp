// author: Oleksii Zhogan

#ifndef __GLFW_SURFACE_HPP__
#define __GLFW_SURFACE_HPP__

#include <core/Surface.hpp>

struct GLFWwindow;

class GLFWSurface : public Surface {
public:

    friend class Application;

	GLFWSurface(Application* app);
	virtual ~GLFWSurface();

    void setTitle(const std::string& title);
    void setGeometry(unsigned int width, unsigned int height);
    void setResizeable(bool flag);
    void setOpenGL(unsigned int major, unsigned int minor);
    void setCoreProfile(bool flag);

    void sendInputEvents();

    bool show();
    bool isOpen();

private:

    void postGLFWInitalize();

private:

    static bool GLFW_LIB_INITED;

private:

    std::string title;
    unsigned int width;
    unsigned int height;
    int openGLMajor;
    int openGLMinor;
    bool resizeable;
    bool corePorfile;

    GLFWwindow* windowHandler;

};

#endif /* __GLFW_SURFACE_HPP__ */
