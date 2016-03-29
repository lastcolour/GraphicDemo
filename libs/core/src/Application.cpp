// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GlutSurface.hpp>

Application::Application(int argc, char* argv[]) {
    args.argc = argc;
    args.argv = argv;
}

bool Application::createSurface() {
    surface.reset(new GlutSurface(this));
    surface->dispaly();
    return true;
}

Application::~Application() {
  
}

CmdArgs& Application::getCMDArgs() {
    return args;
}

int Application::run() {
    if(createSurface()) {
       return main();
    }
    return -1;
}
