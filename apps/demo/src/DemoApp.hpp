#ifndef __DEMO_APP_HPP__
#define __DEMO_APP_HPP__

#include <core\Application.hpp>

class DemoApp : public Application {
  public:
  
    DemoApp(int argc, char* argv[]);
    ~DemoApp();
    
    int run();
};

#endif /* __DEMO_APP_HPP__ */