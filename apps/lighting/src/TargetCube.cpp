#include <TargetCube.hpp>

TargetCube::TargetCube(const char* vertShader, const char* fragShader) :
    LightCube(vertShader, fragShader) {
}

TargetCube::~TargetCube() {
}

void TargetCube::render() {
    LightCube::render();
}