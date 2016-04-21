#include <openGL/ShaderProgram.hpp>
#include <core/ResouceManager.hpp>

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

std::string getProgramLog(GLuint instanceID) {
    GLint tLogSize = 0;
    glGetProgramiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if(tLogSize <= 1) {
        return "?";
    }
    std::string tLogStr;
    tLogStr.resize(tLogSize);
    glGetProgramInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
    return tLogStr;
}

ShaderProgram* ShaderProgram::createProgram(const char* vertShader, const char* fragShader) {
    GLuint vertID = ResourceManager::loadShader(vertShader, GL_VERTEX_SHADER);
    GLuint fragID = ResourceManager::loadShader(fragShader, GL_FRAGMENT_SHADER);
    if(!vertID || !fragID) {
        std::cerr << "[ShaderProgram] Invalid shaders" << std::endl;
        glDeleteShader(fragID);
        glDeleteShader(vertID);
        return nullptr;
    }
    GLuint programID = linkShaders(vertID, fragID);
    if(programID == 0) {
        std::cerr << "[ShaderProgram] Can't link program from:"
                  << "\n[ShaderProgram] - Vertex   : " << vertShader
                  << "\n[ShaderProgram] - Fragment : " << fragShader;
        std::cerr << "\n[ShaderProgram] Problem: " << getProgramLog(programID) << std::endl;
    }

    glDeleteShader(vertID);
    glDeleteShader(fragID);
    if(programID != 0) {
        return new ShaderProgram(programID);
    }
    return nullptr;
}

GLuint ShaderProgram::linkShaders(GLuint vertShaderID, GLuint fragShaderID) {
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    glLinkProgram(programID);
    GLint linked = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if(!linked) {
        glDeleteShader(programID);
        return 0;
    }
    return programID;
}

ShaderProgram* ShaderProgram::createProgram(GLuint vertShaderID, GLuint fragShaderID) {
    GLuint programID = linkShaders(vertShaderID, fragShaderID);
    if(programID == 0) {
        std::cerr << "[ShaderProgram] Can't link program: " << getProgramLog(programID) << std::endl;
    }
    if(programID != 0) {
        return new ShaderProgram(programID);
    }
    return nullptr;
}

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
    glUseProgram(0);
}