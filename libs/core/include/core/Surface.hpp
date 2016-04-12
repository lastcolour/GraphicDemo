// author: Oleksii Zhogan

#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <core\DEFS.hpp>

#include <string>

class Application;


enum class SurfaceBufferMode {
    SINGLE,
    DOUBLE
};


enum class SurfaceColorMode {
    RGB,
    RGBA
};


class LIB_EXPORT_CONV Surface {
public:

	Surface(Application* app);
	virtual ~Surface();

    virtual void setTitle(const std::string& title) = 0;
    virtual void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) = 0;
    virtual void setBufferMode(SurfaceBufferMode mode) = 0;
    virtual void setColorMode(SurfaceColorMode mode) = 0;

    virtual bool initialize() = 0;
    virtual void dispaly() = 0;
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
