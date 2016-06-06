#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <graphics/SceneLight.hpp>

#include <openGL/VAOPipeline.hpp>

#include <memory>

class Light : public SceneLight {
public:

    Light();
    virtual ~Light();

    void update();
    void render();

private:

    static const char* VERT_SHADER;
    static const char* FRAG_SHADER;
    static const float LIGHT_VERTEX_ARR[];
    static const VertexPacking LIGHT_VERTEX_PACK[];

    std::unique_ptr<VAOPipeline> pipePtr;
};

#endif /* __LIGHT_HPP__ */