// author: Oleksii Zhogan

#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core/Appliction.hpp>

class DemoApp : public Appliction {
  public:
    DemoApp(int argc, char* argv[]);
    virtual ~DemoApp();
    
    int run();
};

#endif /* __DEMO_APP_HPP__ */
