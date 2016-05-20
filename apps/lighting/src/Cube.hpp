#ifndef __TARGET_CUBE_HPP__
#define __TRAGET_CUBE_HPP__

#include <GraphicsItem.hpp>

class Cube : public GraphicsItem {
public:

    Cube(const char* vertexShader, const char* fragShader);
    ~Cube();

    void render();
};

#endif /* __TRAGET_CUBE_HPP__ */