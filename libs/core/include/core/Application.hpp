// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core\DEFS.hpp>
#include <core\Surface.hpp>
#include <core\GLManager.hpp>
#include <core\CMDArguments.hpp>

#include <memory>

template class LIB_EXPORT_CONV std::unique_ptr<Surface>;
template class LIB_EXPORT_CONV std::unique_ptr<GLManager>;

class LIB_EXPORT_CONV Application {
public:

    Application(int argc, char* argv[]);
    virtual ~Application();

    virtual void onInitializeEvent();
    virtual void onResizeEvent();
    virtual void onDrawEvent();
    virtual void onAnimateEvent();
    virtual void onMouseEvent();
    virtual void onKeyboardEvent();

    CMDArguments& getCMDArgs();
    int run();

private:

    bool createOpenGL();
    bool createSurface();

private:

    std::unique_ptr<Surface> surface;
    std::unique_ptr<GLManager> gl_Manager;
    CMDArguments cmdArgs;
};

#endif /* __APPLICATION_HPP__*/