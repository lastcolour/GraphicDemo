// author: Oleksii Zhogan (alexzhogan@gmail.com)
// license: WTFPL


#ifndef __MODEL_LOADER_HPP__
#define __MODEL_LOADER_HPP__

#include "PhysicsModel.hpp"

#include <vector>
#include <string>

class ModelLoader {
public:

    ModelLoader();
    ~ModelLoader();
    PhysicsModel* load(int argc, char* argv[]) const;

private:

    PhysicsModel* loadFromCmdArg(int argc, char* argv[]) const;
    PhysicsModel* loadFromUserInput() const;
    PhysicsModel* loadDefault() const;

};

#endif /* __MODEL_LOADER_HPP__  */
