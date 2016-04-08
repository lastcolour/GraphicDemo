// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GlutSurface.hpp>
#include <core/GLEWManager.hpp>

#include <GL/glew.h>

Application::Application(int argc, char* argv[]) :
    cmdArgs(argc, argv) {
}

bool Application::createOpenGL() {
    gl_Manager.reset(new GLEWManager());
    return gl_Manager->initialize();
}

bool Application::createSurface() {
    surface.reset(new GlutSurface(this));
    return surface->initialize();
}

Application::~Application() {
  
}

CMDArguments& Application::getCMDArgs() {
    return cmdArgs;
}


int Application::run() {
    if(createSurface() && createOpenGL()) {
       onInitializeEvent();
       surface->dispaly();
    }
    return 0;
}

void Application::onInitializeEvent() {
}

void Application::onResizeEvent() {
}

void Application::onDrawEvent() {
}

void Application::onAnimateEvent() {
}

void Application::onMouseEvent() {
}

void Application::onKeyboardEvent() {
}
