#include <openGL/ShaderProgram.hpp>

#include <assert.h>


ShaderProgram::ShaderProgram(GLuint progID) :
    programID(progID) {
    assert(progID != 0 && "[ShaderProgram] Creating invalid program");
}

ShaderProgram::~ShaderProgram() {
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    if(tProgram == programID) {
        glUseProgram(0);
    }
    glDeleteProgram(programID);
}

void ShaderProgram::bind() {
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram != programID && "Binding active program");
#endif
    glUseProgram(programID);
}

void ShaderProgram::unbind() {
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram == programID && "Unbinding not active program");
#endif
    glUseProgram(0);
}