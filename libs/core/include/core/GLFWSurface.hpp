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

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    float getShowDuration() const;

private:

    static bool GLFW_LIB_INITED;
    static bool GLEW_LIB_INITED;

    static bool initGLEW();

    static void keyboardCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int keyMode);

    static void mousePosCallback(GLFWwindow* window, double x, double y);
    static void mouseFocusCallback(GLFWwindow* window, int entered);
    static void mouseButtonCallback(GLFWwindow* window, int mouseButton, int action, int keyMode);
    static void mouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

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
};

#endif /* __GLFW_SURFACE_HPP__ */
