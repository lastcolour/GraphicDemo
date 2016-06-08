// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <graphics/SceneElement.hpp>

#include <openGL/VAOPipeline.hpp>

#include <memory>

class Cube : public SceneElement {
public:

    Cube();
    virtual ~Cube();

    virtual void update();
    virtual void render();

private:

    static const char* VERT_SHADER;
    static const char* FRAG_SHADER;
    static const float CUBE_VERTEX_ARR[];
    static const VertexPacking CUBE_VERTEX_PACK[];

    std::unique_ptr<VAOPipeline> pipePtr;
    glm::mat4 transform;
};

#endif /* __CUBE_HPP__ */
