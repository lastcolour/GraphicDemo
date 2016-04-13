// author: Oleksii Zhogan

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <core/DEFS.hpp>

class LIB_EXPORT_CONV Application {
public:

    Application(int argc, char* argv[]);
    virtual ~Application();

    int run();

protected:

    void mainLoop();

private:

    bool initializeApp();
    bool deinitializeApp();
};

#endif /* __APPLICATION_HPP__*/
