// author: Oleksii Zhogan

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/Application.hpp>

class DemoApp : public Application {
public:

    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();
    
    void onAppStartEvent();
    void onGraphicsInitEvent();
    void onResizeEvent(unsigned int width, unsigned int height);
    void onDrawEvent();
};

#endif /* __DEMO_APP_HPP__ */
