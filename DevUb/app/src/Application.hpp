// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL

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

    void restart();
    bool load(int argc, char* argv[]);

    bool initGraphics();
    bool initSurface();
    bool initGLEW();
    void initCallbacks();

    static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

    static Application* ACTIVE_APP;
    static bool GLFW_INITED;

    std::unique_ptr<Simulation> simulPtr;
    GLFWwindow* windowPtr;
    float currTimeP;
    float prevTimeP;
};

#endif /* __APPLICATION_HPP__ */
