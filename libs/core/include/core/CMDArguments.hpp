// author: Oleksii Zhogan

#ifndef __CMD_ARGUMENTS_HPP__
#define __CMD_ARGUMENTS_HPP__

#include <core/DEFS.hpp>

class LIB_EXPORT_CONV CMDArguments {
public:

    CMDArguments(int argc, char* argv[]);
    ~CMDArguments();

    int& getArgc();
    char** getArgv();

private:

    int argcVal;
    char** argvVal;
};

#endif /* __CMD_ARGUMENTS_HPP__ */