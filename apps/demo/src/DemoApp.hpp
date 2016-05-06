// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>

#include <memory>

#include <glm/glm.hpp>

class DemoApp : public OpenGLApplication {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();

protected:

    void onInitEvent();
    void onDrawEvent();
    void onResizeEvent(unsigned int width, unsigned int height);
    void onKeyboardEvent(const KeyboardEvent& keyEvent);

private:

    VAOPipeline* createCube();
    void drawAllCubes();

    glm::mat4 projectionMatrix;
    std::unique_ptr<VAOPipeline> cube;
};

#endif /* __DEMO_APP_HPP__ */
