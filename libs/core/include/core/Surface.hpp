// author: Oleksii Zhogan

#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <core/DEFS.hpp>

class Application;

class LIB_EXPORT_CONV Surface {
public:

	Surface(Application* app);
	virtual ~Surface();

    virtual void setTitle(const char* title) = 0;
    virtual void setGeometry(unsigned int width, unsigned int height) = 0;
    virtual void setResizeable(bool flag) = 0;
    virtual void setOpenGL(unsigned int major, unsigned int minor) = 0;
    virtual void setCoreProfile(bool flag) = 0;

    virtual void sendInputEvents() = 0;

    virtual bool show() = 0;
    virtual bool isOpen() = 0;
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
