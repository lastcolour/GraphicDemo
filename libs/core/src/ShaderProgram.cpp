#include <openGL/ShaderProgram.hpp>
#include <core/Application.hpp>

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

std::string getInfoLog(GLuint instanceID, bool isProgram=false) {
    GLint tLogSize = 0;
    if(!isProgram) {
        glGetShaderiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
        if(tLogSize <= 1) {
            return "?";
        }
        std::string tLogStr;
        tLogStr.resize(tLogSize);
        glGetShaderInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
        return tLogStr;
    }
    // Program case
    glGetProgramiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if(tLogSize <= 1) {
        return "?";
    }
    std::string tLogStr;
    tLogStr.resize(tLogSize);
    glGetProgramInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
    return tLogStr;
}

GLuint loadShader(const std::string& shaderPath, GLenum shaderType) {
    std::string errForStr = "";
    switch(shaderType) {
    case GL_VERTEX_SHADER:
        errForStr = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        errForStr = "fragment";
        break;
    default:
        assert(0 && "[ShaderProgram] Invalid shader type");
        return 0;
    }
    std::ifstream fin(shaderPath);
    if(!fin.is_open()) {
        std::cerr << "[ShaderProgram] Can't open "  << errForStr << " shader file: \"" << shaderPath << "\"" << std::endl;
        return 0;
    }
    std::string shaderStr;
    shaderStr.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    GLuint shaderID = glCreateShader(shaderType);
    const GLchar* vShaderCode = shaderStr.c_str();
    glShaderSource(shaderID, 1, &vShaderCode, nullptr);
    glCompileShader(shaderID);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
    if(compiled != GL_TRUE) {
        std::cerr << "[ShaderProgram] Can't compile " << errForStr << " shader from file: \"" << shaderPath << "\"";
        std::cerr << "\n[ShaderProgram] Problem: " << getInfoLog(shaderID) << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}

ShaderProgram* ShaderProgram::createProgram(const char* vertShader, const char* fragShader) {
    std::string shadersDir = Application::getInstance()->getResourceManager()->getShadersDir();
    std::string vertShaderPath = shadersDir + "/" + vertShader;
    std::string fragShaderPath = shadersDir + "/" + fragShader;
    GLuint vertID = loadShader(vertShaderPath, GL_VERTEX_SHADER);
    GLuint fragID = loadShader(fragShaderPath, GL_FRAGMENT_SHADER);
    if(!vertID || !fragID) {
        std::cerr << "[ShaderProgram] Program creation fail" << std::endl;
        glDeleteShader(fragID);
        glDeleteShader(vertID);
        return nullptr;
    }
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertID);
    glAttachShader(programID, fragID);
    glLinkProgram(programID);
    GLint linked = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if(!linked) {
        std::cerr << "[ShaderProgram] Can't link program from:"
                  << "\n[ShaderProgram] - Vertex   : " << vertShaderPath
                  << "\n[ShaderProgram] - Fragment : " << fragShaderPath;
        std::cerr << "\n[ShaderProgram] Problem: " << getInfoLog(programID, true) << std::endl;
        glDeleteShader(programID);
        programID = 0;
    }
    glDeleteShader(vertID);
    glDeleteShader(fragID);
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
    assert(tProgram != programID && "Use already active program");
#endif
    glUseProgram(programID);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}