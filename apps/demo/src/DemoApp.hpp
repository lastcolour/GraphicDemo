// author: Oleksii Zhogan

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/Application.hpp>

#include <openGL/ShaderProgram.hpp>
#include <openGL/VAOObject.hpp>

#include <memory>

typedef VAOObject<3, GLfloat, 3, GLfloat> Triangle;

class DemoApp : public Application {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();

protected:

    Triangle* createTriangle();

    void onInitEvent();
    void onDrawEvent();

private:

    std::unique_ptr<Triangle> trianglePtr;
};

#endif /* __DEMO_APP_HPP__ */
