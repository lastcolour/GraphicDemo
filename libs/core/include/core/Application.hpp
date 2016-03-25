// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

class Application {
  public:
    Application(int argc, char* argv[]);
    virtual ~Application();
    
    virtual int run();
};

#endif /* __APPLICATION_HPP__*/