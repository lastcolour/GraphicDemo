#ifndef __LIGHTINGAPP_HPP__
#define __LIGHTINGAPP_HPP__

#include <core/OpenGLApplication.hpp>

#include <openGL/VAOPipeline.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <map>

class LightingApp : public OpenGLApplication {
public:

    LightingApp(int argc, char* argv[]);
    virtual ~LightingApp();

protected:
   
    void onResizeEvent(unsigned int width, unsigned int heigth);
    void onMouseEvent(const MouseEvent& mouseE);
    void onKeyboardEvent(const KeyboardEvent& keyE);

    VAOPipeline* createCube(const char* vertShader, const char* fragShader);
    void drawCube();

    VAOPipeline* createLight(const char* vertShader, const char* fragShader);
    void drawLight();

    void processUserInput();

    void mainLoop();
    void drawFrame();

private:

    std::unique_ptr<VAOPipeline> cubePtr;
    std::unique_ptr<VAOPipeline> lightPtr;
    std::unique_ptr<Camera> camera;

    std::map<KeyboardCode, bool> keysPressStatus;

    glm::mat4 cubeTransform;
    glm::mat4 lightTransform;

    float currDrawTimeP;
    float prevDrawTimeP;

};

#endif /* __LIGHTINGAPP_HPP__ */
