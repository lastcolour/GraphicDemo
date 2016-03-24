#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

class Application {
  public:
    Application(int argc, char* argv[]);
    virtual ~Application();
    
    int run();
};

#endif /* __APPLICATION_HPP__*/