// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>
#include <core/FlyCamera.hpp>

#include <map>
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
    void onMouseEvent(const MouseEvent& mouseEvent);

    void chagePolygonMode();
    void processUserInput();

private:

    VAOPipeline* createCube();
    void drawAllCubes();

    std::unique_ptr<VAOPipeline> cube;
    std::unique_ptr<Camera> camera;
    std::map<KeyboardCode, bool> keysPressStatus;
    float currDrawTimeP;
    float prevDrawTimeP;
};

#endif /* __DEMO_APP_HPP__ */
