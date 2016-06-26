// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL

#include "Application.hpp"

#include <iostream>

const char* INFO_MESAGE = \
"This program developed by Oleksii Zhogan (alexzhogan@gmail.com)\n"\
"License: WTFPL";

int main(int argc, char* argv[]) {
    std::cout << INFO_MESAGE << std::endl;
    Application app(argc, argv);
    return app.run();
}
