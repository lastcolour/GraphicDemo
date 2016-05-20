#ifndef __LIGHTINGAPP_HPP__
#define __LIGHTINGAPP_HPP__

#include <GraphicsScene.hpp>

#include <core/OpenGLApplication.hpp>

#include <memory>


class LightingApp : public OpenGLApplication {
public:

    LightingApp(int argc, char* argv[]);
    virtual ~LightingApp();

protected:
   
    void onMouseEvent(const MouseEvent& mouseE);
    void onKeyboardEvent(const KeyboardEvent& keyE);

    void initScene();
    void mainLoop();
    void drawFrame();

private:

    std::unique_ptr<IOCameraController> ioController;
    std::unique_ptr<GraphicsScene> scenePtr;
};

#endif /* __LIGHTINGAPP_HPP__ */
