#ifndef __LIGHTINGAPP_HPP__
#define __LIGHTINGAPP_HPP__

#include <core/OpenGLApplication.hpp>

#include <openGL/VAOPipeline.hpp>

#include <glm/glm.hpp>

#include <Scene.hpp>
#include <InputController.hpp>

#include <memory>
#include <map>

class LightingApp : public OpenGLApplication {
public:

    LightingApp(int argc, char* argv[]);
    virtual ~LightingApp();

protected:
   
    Scene* createScene();

    void onResizeEvent(unsigned int width, unsigned int heigth);
    void onMouseEvent(const MouseEvent& mouseE);
    void onKeyboardEvent(const KeyboardEvent& keyE);

    void mainLoop();

private:

    std::unique_ptr<Scene> scenePtr;
    std::unique_ptr<InputController> inpController;

    float currDrawTimeP;
    float prevDrawTimeP;

};

#endif /* __LIGHTINGAPP_HPP__ */
