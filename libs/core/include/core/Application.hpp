// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core\DEFS.hpp>
#include <core\Surface.hpp>

#include <memory>

struct CmdArgs
{
    int argc;
    char** argv;
};

template class LIB_EXPORT_CONV std::unique_ptr<Surface>;

class LIB_EXPORT_CONV Application {
  public:

    Application(int argc, char* argv[]);
    virtual ~Application();
    
    CmdArgs& getCMDArgs();

    int run();

    virtual bool createSurface();
    virtual int main() = 0;

private:

    std::unique_ptr<Surface> surface;

    CmdArgs args;
};

#endif /* __APPLICATION_HPP__*/