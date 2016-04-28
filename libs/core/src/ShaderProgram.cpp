// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/ShaderProgram.hpp>

#include <iostream>
#include <string>
#include <assert.h>
#include <vector>

std::vector<std::string> getAllUniformsNames(GLuint programID) {
    std::vector<std::string> allUniforms;
    GLint activUniforms = 0;
    glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &activUniforms);
    if(activUniforms > 0) {
        std::vector<GLchar> tStrBuffer(OPENGL_STR_BUF_SIZE);
        for(GLint i = 0; i < activUniforms; ++i) {
            GLsizei tLen = 0;
            GLint tSize = 0;
            GLenum tType = GL_NONE;
            glGetActiveUniform(programID, i, OPENGL_STR_BUF_SIZE, &tLen, &tSize, &tType, &tStrBuffer[0]);
            allUniforms.push_back(std::string(&tStrBuffer[0]));
        }
    }
    return allUniforms;
}

ShaderProgram::ShaderProgram(GLuint progID) :
    programID(progID) {
    assert(progID != 0 && "[ShaderProgram] Creating invalid program");
}

GLuint ShaderProgram::getID() const {
    return programID;
}

ShaderProgram::~ShaderProgram() {
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    if(tProgram == programID) {
        glUseProgram(0);
    }
    glDeleteProgram(programID);
}

void ShaderProgram::bind() const {
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram != programID && "Binding active program");
#endif
    glUseProgram(programID);
}

GLint ShaderProgram::getUniformLocation(const char* name) const {
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram == programID && "Set uniform for not bounded program");
#endif

    GLint unifLoc = glGetUniformLocation(programID, name);

#ifdef GD_CORE_LIB_DEBUG
    if(unifLoc == -1) {
        reportUniformNameError(name);
    }
#endif 
    return unifLoc;
}

void ShaderProgram::reportUniformNameError(const char* name) const {
    std::vector<std::string> allUniforms = getAllUniformsNames(programID);
    std::string tMessagePrefix;
    tMessagePrefix = tMessagePrefix + "[ShaderProgram:" + std::to_string(programID) + "] ";
    if(allUniforms.size() == 0) {
        std::cerr << tMessagePrefix.c_str() << "Can't find uniform: \"" << name 
            << "\"; Program does't have any uniform\n";
    } else {
        std::cerr << tMessagePrefix.c_str() << "Can't find uniform: \"" << name 
            << "\"; Program, containe next uniforms\n";
        for(const auto& tName : allUniforms) {
            std::cerr << tMessagePrefix.c_str() << " - \"" << tName << "\"" << std::endl;
        }
    }
}

void ShaderProgram::setUniform1f(const char* name, float x) const {
    GLint unifLoc = -1;
    if((unifLoc = getUniformLocation(name)) != -1) {
        glUniform1f(unifLoc, x);
    }
}

void ShaderProgram::setUniform4f(const char* name, float x, float y, float z, float w) const {
    GLint unifLoc = -1;
    if((unifLoc = getUniformLocation(name)) != -1) {
        glUniform4f(unifLoc, x, y, z, w);
    }
}

void ShaderProgram::unbind() const {
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram == programID && "Unbinding not active program");
#endif
    glUseProgram(0);
}