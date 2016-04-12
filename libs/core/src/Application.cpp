// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>
#include <core/GLEWManager.hpp>

#include <GL/glew.h>

Application::Application(int argc, char* argv[]) :
    cmdArgs(argc, argv),
    surface(new GLFWSurface(this)),
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

            // start main loop
            mainLoop();
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

void Application::mainLoop() {
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
