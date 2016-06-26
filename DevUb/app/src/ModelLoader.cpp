// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL

#include "ModelLoader.hpp"

#include <vector>
#include <string>
#include <iostream>

ModelLoader::ModelLoader() {
}

ModelLoader::~ModelLoader() {
}

PhysicsModel* ModelLoader::loadFromCmdArg(int argc, char* argv[]) const {
    std::cout << "[ModelLoader] Loading from cmd args not supported. Skipping" << std::endl;
    return loadFromUserInput();
}

PhysicsModel* ModelLoader::loadDefault() const {
    PhysicsModel* model = new PhysicsModel();
    model->angle = 90.f;
    model->speed = 10.f;
    model->weight = 10.f;
    model->jump = true;
    model->lossEnger = 0.8;
    model->height = 0.f;
    return model;
}

PhysicsModel* ModelLoader::loadFromUserInput() const {
    float angle = 0.f;
    float speed = 0.f;
    float weight = 0.f;
    float lossEnger = 0.f;
    float height = 0.f;
    bool jump = false;
    char tCh;
    std::cout << " - Use default (Y/N): "; std::cin >> tCh;
    if(tCh == 'y' || tCh == 'Y') {
        return loadDefault();
    }
    std::cout << " - Angle degree in (0;90]: "; std::cin >> angle;
    std::cout << " - Speed (greater 0): "; std::cin >> speed;
    std::cout << " - Weight (greater 0): "; std::cin >> weight;
    std::cout << " - Jump (Y/N): "; std::cin >> tCh;
    if(tCh == 'y' || tCh == 'Y') {
        jump = true;
        std::cout << " - Energy loss in (0;1): "; std::cin >> lossEnger;
    }
    PhysicsModel* model = new PhysicsModel();
    model->angle = angle;
    model->speed = speed;
    model->weight = weight;
    model->jump = jump;
    model->lossEnger = lossEnger;
    model->height = height;
    return model;
}

PhysicsModel* ModelLoader::load(int argc, char* argv[]) const {
    if(argc == 1) {
        std::cout << "[ModelLoader] Please specifies model params:" << std::endl;
        return loadFromUserInput();
    }
    return loadFromCmdArg(argc, argv);
}
