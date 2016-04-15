// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core/DEFS.hpp>
#include <core/Surface.hpp>

#include <memory>

template class LIB_EXPORT_CONV std::unique_ptr<Surface>;

class LIB_EXPORT_CONV Application {
public:

    Application(int argc, char* argv[]);
    virtual ~Application();

    int run();

protected:

    virtual void onInitEvent();
    virtual void onDeinitEvent();
    virtual void onResizeEvent(unsigned int width, unsigned int height);
    virtual void onDrawEvent();

    Surface* getSurface();

private:

    bool appDeinit();
    bool appInit();
    
    void mainLoop();

private:

    std::unique_ptr<Surface> surfacePtr;

private:

    friend class GLFWSurface;
};

#endif /* __APPLICATION_HPP__*/
