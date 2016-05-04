// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/OpenGLApplication.hpp>
#include <openGL/VAOPipeline.hpp>
#include <memory>

class DemoApp : public OpenGLApplication {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();

protected:

    void onInitEvent();
    void onDrawEvent();
    void onKeyboardEvent(const KeyboardEvent& keyEvent);

private:

     std::unique_ptr<VAOPipeline> triangle;
};

#endif /* __DEMO_APP_HPP__ */
