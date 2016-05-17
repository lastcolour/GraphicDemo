// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include <core/VisualApplication.hpp>
#include <cassert>

class Surface {
public:

    Surface(VisualApplication* app);
    virtual ~Surface();

    virtual void setTitle(const char* title) = 0;
    virtual void setGeometry(unsigned int width, unsigned int height) = 0;
    virtual void setResizeable(bool flag) = 0;
    virtual void setOpenGL(unsigned int major, unsigned int minor) = 0;
    virtual void setCoreProfile(bool flag) = 0;
    virtual void setVisibleCursor(bool flag) = 0;
    virtual void setVsyncOn(bool flag) = 0;

    virtual void sendEvents() = 0;

    virtual bool show() = 0;
    virtual bool isOpen() = 0;
    virtual void close() = 0;
    virtual void swapBuffers() = 0;

    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;
    virtual float getShowDuration() const = 0;

protected:

    static void sendReDrawEvent();
    static void sendKeyboardEvent(const KeyboardEvent& keyEvent);
    static void sendMouseEvent(const MouseEvent& mouseEvent);
    static void sendResizeEvent(unsigned int w, unsigned int h);

private:

    Surface();
    Surface& operator=(const Surface&);
    Surface(const Surface&);

private:

    static VisualApplication* application;
};

#endif /* __SURFACE_HPP__ */
