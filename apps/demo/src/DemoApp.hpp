// author: Oleksii Zhogan

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/Application.hpp>

#include <openGL/ShaderProgram.hpp>

#include <memory>

class DemoApp : public Application {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();

protected:

    void onInitEvent();
    void onDrawEvent();

private:

    std::unique_ptr<ShaderProgram> programGL;
    GLuint arrayID;
};

#endif /* __DEMO_APP_HPP__ */
