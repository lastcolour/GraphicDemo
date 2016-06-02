#include <Cube.hpp>

const char* Cube::VERT_SHADER = "shaders/cubeVert.glsl";
const char* Cube::FRAG_SHADER = "shaders/cubeFrag.glsl";

const float Cube::CUBE_VERTEX_ARR[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

const VertexPacking Cube::CUBE_VERTEX_PACK[] = {
    VertexPacking::VEC3,
    VertexPacking::NONE
};

Cube::Cube() :
    pipePtr(new VAOPipeline()) {

    ShaderProgram tProgram(VERT_SHADER, FRAG_SHADER);
    if (!tProgram.isValid()) {
        return;
    }
    pipePtr->setVertexBuffer(sizeof(CUBE_VERTEX_ARR), CUBE_VERTEX_ARR, CUBE_VERTEX_PACK, GL_DYNAMIC_DRAW);
    pipePtr->setProgram(std::move(tProgram));
}

Cube::~Cube() {
}

void Cube::translate() {
}

void Cube::rotate() {
}

void Cube::scale() {
}

void Cube::update() {
}

void Cube::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Cube::draw() {
    pipePtr->getProgram()->setUniformMat4fv("CameraMat", getScene()->getCameraMat());
    pipePtr->drawAll();
}