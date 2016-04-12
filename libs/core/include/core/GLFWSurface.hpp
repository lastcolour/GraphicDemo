// author: Oleksii Zhogan

#ifndef __GLFW_SURFACE_HPP__
#define __GLFW_SURFACE_HPP__

#include <core/Surface.hpp>

#include <memory>

class GLFWDataHandler;

class GLFWSurface : public Surface {
public:
	GLFWSurface(Application* app);
	virtual ~GLFWSurface();

    bool initialize();
	void dispaly();
    void swapBuffers();

    void setBufferMode(SurfaceBufferMode mode);
    void setColorMode(SurfaceColorMode mode);

    void setTitle(const std::string& title);
    void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height);


private:

private:

    bool inited;
    std::unique_ptr<GLFWDataHandler> dataHandler;

};

#endif /* __GLFW_SURFACE_HPP__ */
