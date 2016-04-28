// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/ShaderProgram.hpp>

#include <memory>

class DemoApp : public OpenGLApplication {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();

protected:

    void onInitEvent();
    void onDrawEvent();
    void onKeyboardEvent(const KeyboardEvent& keyEvent);

    GLuint createFirstTriangle();
    GLuint createSecondTriangle();

private:

    GLuint firstTriangle;
    GLuint secondTriangle;
    std::unique_ptr<ShaderProgram> firstProgram;
    std::unique_ptr<ShaderProgram> secondProgram;
};

#endif /* __DEMO_APP_HPP__ */
