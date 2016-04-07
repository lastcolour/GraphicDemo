// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core\DEFS.hpp>
#include <core\Surface.hpp>
#include <core\CMDArguments.hpp>

#include <memory>

template class LIB_EXPORT_CONV std::unique_ptr<Surface>;

class LIB_EXPORT_CONV Application {
public:

    Application(int argc, char* argv[]);
    virtual ~Application();

    virtual void onDrawEvent();
    virtual void onAnimateEvent();
    virtual void onMouseEvent();
    virtual void onKeyboardEvent();

    CMDArguments& getCMDArgs();
    int run();

protected:

    virtual int main() = 0;

private:

    bool createOpenGLContext();
    bool createSurface();

private:

    std::unique_ptr<Surface> surface;
    CMDArguments cmdArgs;
};

#endif /* __APPLICATION_HPP__*/