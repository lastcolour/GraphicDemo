#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <SceneElement.hpp>

#include <openGL/VAOPipeline.hpp>

#include <memory>

class Light : public SceneElement {
public:

    Light();
    virtual ~Light();

    void setPosition(const glm::vec3& pos);

    void translate();
    void rotate();
    void scale();

    void update();
    void draw();

private:

    static const char* VERT_SHADER;
    static const char* FRAG_SHADER;
    static const float LIGHT_VERTEX_ARR[];
    static const VertexPacking LIGHT_VERTEX_PACK[];

    std::unique_ptr<VAOPipeline> pipePtr;
    glm::vec3 position;
};

#endif /* __LIGHT_HPP__ */