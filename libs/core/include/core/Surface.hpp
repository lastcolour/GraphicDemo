// author: Oleksii Zhogan

#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <core\DEFS.hpp>
#include <core\SurfaceDefs.hpp>

#include <string>

class Application;


class LIB_EXPORT_CONV Surface {
public:

	Surface(Application* app);
	virtual ~Surface();

    virtual void setTitle(const std::string& title) = 0;
    virtual void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) = 0;
    virtual void setBufferMode(SurfaceBufferMode mode) = 0;
    virtual void setColorMode(SurfaceColorMode mode) = 0;
    virtual void setOpenGLVersion(unsigned int major, unsigned int minor) = 0;

    virtual void show() = 0;
    virtual void close() = 0;
    virtual void swapBuffers() = 0;

protected:

    static Application* getApp();

private:

    static Application *appListener;
};


// Inline methods implementation

inline
Application* Surface::getApp() { return appListener; }

#endif /* __SURFACE_HPP__ */
