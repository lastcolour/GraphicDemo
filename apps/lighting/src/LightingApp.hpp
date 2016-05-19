#ifndef __LIGHTINGAPP_HPP__
#define __LIGHTINGAPP_HPP__

#include <IOCameraController.hpp>
#include <TargetCube.hpp>
#include <LightCube.hpp>

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>

#include <memory>


class LightingApp : public OpenGLApplication {
public:

    LightingApp(int argc, char* argv[]);
    virtual ~LightingApp();

protected:

    void initSurface();
    void initGeomtry();
   
    void onMouseEvent(const MouseEvent& mouseE);
    void onKeyboardEvent(const KeyboardEvent& keyE);

    void mainLoop();
    void drawFrame();

    VAOPipeline* createCube();
    VAOPipeline* createLightPoint();

private:

    std::unique_ptr<IOCameraController> ioController;
    std::unique_ptr<LightCube> lightCube;
    std::unique_ptr<TargetCube> targetCube;
};

#endif /* __LIGHTINGAPP_HPP__ */
