// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __GLFW_SURFACE_HPP__
#define __GLFW_SURFACE_HPP__

#include <core/Surface.hpp>

#include <string>

struct GLFWwindow;

class GLFWSurface : public Surface {
public:

    GLFWSurface(VisualApplication* app);
	virtual ~GLFWSurface();

    void setTitle(const char* title);
    void setGeometry(unsigned int width, unsigned int height);
    void setResizeable(bool flag);
    void setOpenGL(unsigned int major, unsigned int minor);
    void setCoreProfile(bool flag);

    void sendEvents();

    bool show();
    bool isOpen();
    void close();
    void swapBuffers();

private:

    static bool GLFW_LIB_INITED;
    static bool GLEW_LIB_INITED;

    static bool initGLEW();

    static void keyboardCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int keyMode);
    static void mouseCallBack();

    void initCallbacks();

private:

    std::string title;
    GLFWwindow* windowPtr;
    unsigned int width;
    unsigned int height;
    int openGLMajor;
    int openGLMinor;
    bool resizeable;
    bool corePorfile;

private:

    friend class Application;
};

#endif /* __GLFW_SURFACE_HPP__ */
