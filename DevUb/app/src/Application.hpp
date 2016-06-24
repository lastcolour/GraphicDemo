#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include "Simulation.hpp"

#include <memory>

struct GLFWwindow;

class Application {
public:

    Application(int argc, char* argv[]);
    ~Application();

    int run();

private:

    bool parseArgs(int argc, char* argv[]);

    bool initGraphics();
    bool initSurface();
    bool initGLEW();
    void initCallbacks();

private:

    static bool GLFW_INITED;

    GLFWwindow* windowPtr;
    std::unique_ptr<Simulation> simulPtr;
    float currTimeP;
    float prevTimeP;
};

#endif /* __APPLICATION_HPP__ */