// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __VISUAL_APPLICATION_HPP__
#define __VISUAL_APPLICATION_HPP__

#include <core/DEFS.hpp>
#include <core/KeyboardEvent.hpp>

class LIB_EXPORT_CONV VisualApplication {
public:

    VisualApplication() {}
    virtual ~VisualApplication() {}

    virtual void setSurfaceTitle(const char* title) = 0;
    virtual void setSurfaceGeometry(unsigned int width, unsigned int height) = 0;
    virtual void setSurfaceResizable(bool flag) = 0;

protected:

    virtual void checkInitErrors() = 0;
    virtual void checkResizerrors() = 0;
    virtual void checkKeyboardErrors() = 0;
    virtual void checkDrawErrors() = 0;

    void appInitRequest() {
        onInitEvent();
        checkInitErrors();
    }

    void appResizeRequest(unsigned int width, unsigned int heigth) {
        onResizeEvent(width, heigth);
        checkResizerrors();
    }

    void appKeyboardRequest(const KeyboardEvent& keyEvent) {
        onKeyboardEvent(keyEvent);
        checkKeyboardErrors();
    }

    void appDrawRequest() {
        onDrawEvent();
        checkDrawErrors();
    }

    virtual void onResizeEvent(unsigned int width, unsigned int heigth) {}
    virtual void onKeyboardEvent(const KeyboardEvent& keyEvent) {}
    virtual void onDrawEvent() {}
    virtual void onMouseEvent() {}
    virtual void onInitEvent() {}

protected:

    friend class Surface;
};

#endif /* __VISUAL_APPLICATION_HPP__ */