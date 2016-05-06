// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __VISUAL_APPLICATION_HPP__
#define __VISUAL_APPLICATION_HPP__

#include <core/DEFS.hpp>
#include <core/KeyboardEvent.hpp>
#include <core/MouseEvent.hpp>

class LIB_EXPORT_CONV VisualApplication {
public:

    VisualApplication() {}
    virtual ~VisualApplication() {}

    virtual void setSurfaceTitle(const char* title) = 0;
    virtual void setSurfaceGeometry(unsigned int width, unsigned int height) = 0;
    virtual void setSurfaceResizable(bool flag) = 0;

    virtual unsigned int getWidth() const = 0;
    virtual unsigned int getHeight() const = 0;

protected:

    void appInitRequest() {
        onInitEvent();
    }

    void appResizeRequest(unsigned int width, unsigned int heigth) {
        onResizeEvent(width, heigth);
    }

    void appKeyboardRequest(const KeyboardEvent& keyEvent) {
        onKeyboardEvent(keyEvent);
    }

    void appDrawRequest() {
        onDrawEvent();
    }

    void appMouseRequest(const MouseEvent& mouseEvent) {
        onMouseEvent(mouseEvent);

    }

    virtual void onResizeEvent(unsigned int width, unsigned int heigth) {}
    virtual void onKeyboardEvent(const KeyboardEvent& keyEvent) {}
    virtual void onMouseEvent(const MouseEvent& mouseEvent) {}
    virtual void onDrawEvent() {}
    virtual void onInitEvent() {}

protected:

    friend class Surface;
};

#endif /* __VISUAL_APPLICATION_HPP__ */