// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GlutSurface.hpp>


Application::Application(int argc, char* argv[]) :
    cmdArgs(argc, argv) {
}

bool Application::createSurface() {
    surface.reset(new GlutSurface(this));
    surface->dispaly();
    return true;
}

Application::~Application() {
  
}

CMDArguments& Application::getCMDArgs() {
    return cmdArgs;
}

int Application::run() {
    if(createSurface()) {
       return main();
    }
    return -1;
}

void Application::onDrawEvent() {
}

void Application::onAnimateEvent() {
}

void Application::onMouseEvent() {
}

void Application::onKeyboardEvent() {
}
