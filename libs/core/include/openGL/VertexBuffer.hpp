#ifndef __VERTEX_BUFFER_HPP__
#define __VERTEX_BUFFER_HPP__

#include <core/DEFS.hpp>

#include <glm/glm.hpp>

class LIB_EXPORT_CONV VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    static VertexBuffer* createCube(float edgeLen, const glm::vec3& center = glm::vec3(0));

};

#endif /* __VERTEX_BUFFER_HPP__ */
