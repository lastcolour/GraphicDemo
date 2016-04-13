// author: Oleksii Zhogan

#ifndef __GLFW_SURFACE_HPP__
#define __GLFW_SURFACE_HPP__

#include <core/Surface.hpp>
#include <core/GLFWDataHandler.hpp>

#include <memory>

class GLFWSurface : public Surface {
public:

    friend class Application;

	GLFWSurface(Application* app);
	virtual ~GLFWSurface();

    
	void show();
    void close();
    void swapBuffers();

    void setBufferMode(SurfaceBufferMode mode);
    void setColorMode(SurfaceColorMode mode);
    void setOpenGLVersion(unsigned int major, unsigned int minor);

    void setTitle(const std::string& title);
    void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);

private:

    std::unique_ptr<GLFWDataHandler> dataHandler;

private:


    static bool initialize();
    static bool deinitialize();

    static bool GLFW_LIB_INITED;

};

#endif /* __GLFW_SURFACE_HPP__ */
