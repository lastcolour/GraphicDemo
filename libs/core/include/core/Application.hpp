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

    virtual void onResizeEvent(unsigned int width, unsigned int height);
    virtual void onDrawEvent();

protected:

    Surface* getSurface();

    virtual void onInitEvent();
    virtual void onDeinitEvent();

private:

    bool appDeinit();
    bool appInit();
    
    void mainLoop();

private:

    std::unique_ptr<Surface> surfacePtr;
};

#endif /* __APPLICATION_HPP__*/
