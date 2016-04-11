// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GlutSurface.hpp>
#include <core/GLEWManager.hpp>

#include <GL/glew.h>

Application::Application(int argc, char* argv[]) :
    cmdArgs(argc, argv),
    surface(new GlutSurface(this)),
    gl_Manager(new GLEWManager()) {
}

bool Application::createOpenGL() {
    return gl_Manager->initialize();
}

bool Application::createSurface() {
    return surface->initialize();
}

Application::~Application() {
}

CMDArguments& Application::getCMDArgs() {
    return cmdArgs;
}

int Application::run() {
    try {
        onAppStartEvent();
        if(createSurface() && createOpenGL()) {
            onGraphicsInitEvent();
            surface->dispaly(); 
        }
    } catch( ... ) {
        return -1;
    }
    onAppFinishEvent();
    return 0;
}


Surface* Application::getSurface() {
    return surface.get();
}

/* Default empty implementation */
void Application::onAppStartEvent() {
}

void Application::onAppFinishEvent() {
}

void Application::onGraphicsInitEvent() {
}

void Application::onResizeEvent(unsigned int width, unsigned int height) {
}

void Application::onDrawEvent() {
}

void Application::onAnimateEvent() {
}

void Application::onMouseEvent() {
}

void Application::onKeyboardEvent() {
}
