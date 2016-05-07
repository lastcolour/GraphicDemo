// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>
#include <core/FlyCamera.hpp>

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

    void chagePolygonMode();

private:

    VAOPipeline* createCube();
    void drawAllCubes();

    std::unique_ptr<VAOPipeline> cube;
    std::unique_ptr<FlyCamera> camera;
};

#endif /* __DEMO_APP_HPP__ */
