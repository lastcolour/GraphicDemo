// author: Oleksii Zhogan

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

    GLuint createTriangle();

private:

    GLuint trinanglID;
    std::unique_ptr<ShaderProgram> programPtr;
};

#endif /* __DEMO_APP_HPP__ */
