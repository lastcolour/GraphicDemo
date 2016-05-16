#ifndef __LIGHTINGAPP_HPP__
#define __LIGHTINGAPP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>

#include <memory>


class LightingApp : public OpenGLApplication {
public:

    LightingApp(int argc, char* argv[]);
    virtual ~LightingApp();

protected:

    void onInitEvent();
    void onReDrawEvent();

    void mainLoop();

    VAOPipeline* createCube();
    VAOPipeline* createLightPoint();

private:

    std::unique_ptr<VAOPipeline> lightPoint;
    std::unique_ptr<VAOPipeline> cube;
};

#endif /* __LIGHTINGAPP_HPP__ */
