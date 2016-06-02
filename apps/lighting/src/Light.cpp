#include <Light.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* Light::VERT_SHADER = "shaders/lightVert.glsl";
const char* Light::FRAG_SHADER = "shaders/lightFrag.glsl";

const float Light::LIGHT_VERTEX_ARR[] = {
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

const VertexPacking Light::LIGHT_VERTEX_PACK[] = {
    VertexPacking::VEC3,
    VertexPacking::NONE
};

Light::Light() :
    pipePtr(new VAOPipeline()) {

    ShaderProgram tProgram(VERT_SHADER, FRAG_SHADER);
    if (!tProgram.isValid()) {
        return;
    }
    pipePtr->setVertexBuffer(sizeof(LIGHT_VERTEX_ARR), LIGHT_VERTEX_ARR, LIGHT_VERTEX_PACK, GL_DYNAMIC_DRAW);
    pipePtr->setProgram(std::move(tProgram));
}

Light::~Light() {
}

void Light::draw() {
    glm::mat4 transform;
    transform = glm::scale(transform, glm::vec3(0.2f));
    transform = glm::translate(transform, position);
    pipePtr->getProgram()->setUniformMat4fv("CameraMat", getScene()->getCameraMat());
    pipePtr->getProgram()->setUniformMat4fv("TransformMat", glm::value_ptr(transform));
    pipePtr->drawAll();
}

void Light::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Light::update() {
}

void Light::translate() {
}

void Light::rotate() {
}

void Light::scale() {
}