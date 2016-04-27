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

    virtual int run() = 0;

protected:

    virtual void onResizeEvent(unsigned int width, unsigned int heigth) {}
    virtual void onKeyboardEvent(const KeyboardEvent& keyEvent) {}
    virtual void onDrawEvent() {}
    virtual void onMouseEvent() {}
    virtual void onInitEvent() {}

protected:

    friend class Surface;
};

#endif /* VisualApplication */