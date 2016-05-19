#ifndef __TARGET_CUBE_HPP__
#define __TRAGET_CUBE_HPP__

#include <LightCube.hpp>

class TargetCube : public LightCube {
public:

    TargetCube(const char* vertexShader, const char* fragShader);
    ~TargetCube();

    void render();
};

#endif /* __TRAGET_CUBE_HPP__ */