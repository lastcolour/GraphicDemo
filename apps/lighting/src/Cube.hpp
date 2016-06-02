#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include <SceneElement.hpp>

#include <openGL/VAOPipeline.hpp>

#include <memory>

class Cube : public SceneElement {
public:

    Cube();
    virtual ~Cube();

    void setPosition(const glm::vec3& pos);

    void translate();
    void rotate();
    void scale();

    void update();
    void draw();

private:

    static const char* VERT_SHADER;
    static const char* FRAG_SHADER;
    static const float CUBE_VERTEX_ARR[];
    static const VertexPacking CUBE_VERTEX_PACK[];

    std::unique_ptr<VAOPipeline> pipePtr;
    glm::mat4 transform;
    glm::vec3 position;
};

#endif /* __CUBE_HPP__ */
