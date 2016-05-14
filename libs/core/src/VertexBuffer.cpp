#include <openGL/VertexBuffer.hpp>

VertexBuffer::VertexBuffer() {

}

VertexBuffer::~VertexBuffer()
{
}

VertexBuffer* VertexBuffer::createCube(float edgeLen, const glm::vec3& center) {
    return new VertexBuffer();
}


