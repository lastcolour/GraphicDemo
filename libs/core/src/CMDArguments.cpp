// author: Oleksii Zhogan

#include <core/CMDArguments.hpp>

CMDArguments::CMDArguments(int argc, char* argv[]) : 
    argcVal(argc), argvVal(argv) {
}

CMDArguments::~CMDArguments() {
}

int& CMDArguments::getArgc() {
    return argcVal;
}

char** CMDArguments::getArgv() {
    return argvVal;
}