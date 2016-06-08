// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <Cube.hpp>

#include <graphics/SceneLight.hpp>
#include <graphics/SceneCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* Cube::VERT_SHADER = "shaders/cubeVert.glsl";
const char* Cube::FRAG_SHADER = "shaders/cubeFrag.glsl";

const float Cube::CUBE_VERTEX_ARR[] = {
     // Postion : vec3 | Normal : vec3
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const VertexPacking Cube::CUBE_VERTEX_PACK[] = {
    VertexPacking::VEC3,
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

void Cube::update() {
}

void Cube::render() {
    pipePtr->getProgram()->setUniformMat4fv("CameraMat", getScene()->getCameraMat());
    glm::mat4 transform;
    transform = glm::translate(transform, getPosition());
    pipePtr->getProgram()->setUniformMat4fv("WorldMat", glm::value_ptr(transform));
    pipePtr->getProgram()->setUniform4f("FragColor", 1.f, 0.f, 0.f, 1.f);
    SceneLight* tLight = nullptr;
    for (auto ligthElem : getScene()->getLights()) {
        tLight = ligthElem;
        break;
    }
    // add lighting
    if (tLight != nullptr) {
        const glm::vec4& tColor = tLight->getColor();
        pipePtr->getProgram()->setUniform4f("LightColor", tColor.r, tColor.g, tColor.b, tColor.a);

        const glm::vec3& tPos = tLight->getPosition();
        pipePtr->getProgram()->setUniform3f("LightPos", tPos.x, tPos.y, tPos.z);

        const glm::vec3& tCameraPos = getScene()->getCamera()->getPosition();
        pipePtr->getProgram()->setUniform3f("ViewPos", tCameraPos.x, tCameraPos.y, tCameraPos.z);
    }

    pipePtr->drawAll();
}