#ifndef __ARG_PARSER_HPP__
#define __ARG_PARSER_HPP__

#include "PhysicsModel.hpp"

#include <vector>
#include <string>

class ArgParser {
public:

    ArgParser();
    ~ArgParser();
    PhysicsModel* parse(int argc, char* argv[]);

private:

    bool tryUpdateModel(const std::vector<std::string>& context, PhysicsModel* model);

};

#endif /* __ARG_PARSER_HPP__  */