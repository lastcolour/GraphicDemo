#include "ArgParser.hpp"

#include <vector>
#include <string>

ArgParser::ArgParser() {
}

ArgParser::~ArgParser() {
}

PhysicsModel* ArgParser::parse(int argc, char* argv[]) {
    //if (argc <= 1) {
    //    return nullptr;
    //}
    std::vector<std::string> tContex;
    PhysicsModel* model = new PhysicsModel();
    model->angle = 45.f;
    model->speed = 10.f;
    model->weight = 10.f;
    model->jump = true;
    model->lossEnger = 0.25;
    return model;
}

bool ArgParser::tryUpdateModel(const std::vector<std::string>& context, PhysicsModel* model) {
    return true;
}