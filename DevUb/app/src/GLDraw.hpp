#ifndef __GL_DRAW_HPP__
#define __GL_DRAW_HPP__

#include <GL/glew.h>

struct GLDrawData
{
    GLuint progID;
    GLuint vaoID;
    GLuint bufferID;

    GLDrawData() : progID(0), vaoID(0), bufferID(0) {}
    GLDrawData(const GLDrawData& draw) : progID(draw.progID), vaoID(draw.vaoID), bufferID(draw.bufferID) {}
    ~GLDrawData() {}


    void clear() {
        glDeleteProgram(progID);
        glDeleteBuffers(1, &bufferID);
        glDeleteVertexArrays(1, &vaoID);
    }
    bool isValid() const { return progID != 0 && vaoID != 0 && bufferID != 0; }
};

#endif /* __GL_DRAW_HPP__ */
