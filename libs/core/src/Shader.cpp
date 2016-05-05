// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/Shader.hpp>

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

std::string getShaderLog(GLuint instanceID) {
    GLint tLogSize = 0;
    glGetShaderiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if(tLogSize <= 1) {
        return "?";
    }
    std::string tLogStr;
    tLogStr.resize(tLogSize);
    glGetShaderInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
    return tLogStr;
}

GLuint loadShader(const char* shaderPath, GLenum shaderType) {
    std::string errForStr = "";
    switch(shaderType) {
    case GL_VERTEX_SHADER:
        errForStr = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        errForStr = "fragment";
        break;
    default:
        assert(0 && "[Shader] Invalid shader type");
        return 0;
    }
    std::ifstream fin(shaderPath);
    if(!fin.is_open()) {
        std::cerr << "[Shader] Can't open "  << errForStr << " shader file: \"" << shaderPath << "\"" << std::endl;
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
        std::cerr << "[Shader] Can't compile " << errForStr << " shader from file: \"" << shaderPath << "\"";
        std::cerr << "\n[Shader] Problem: " << getShaderLog(shaderID) << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}

Shader::Shader(const char* filename, GLenum type) :
    Resource(),
    shaderID(0),
    shaderType(GL_NONE) {
    switch (type)
    {
    case GL_VERTEX_SHADER:
    case GL_FRAGMENT_SHADER:
        shaderID = loadShader(getFullPath(filename), type);
        shaderType = type;
        break;
    default:
        assert(0 && "Invalid shader type");
    }
}

Shader::Shader(Shader&& shader) :
    shaderID(shader.shaderID),
    shaderType(shader.shaderType) {
    shader.shaderID = 0;
    shader.shaderType = GL_NONE;
}

Shader& Shader::operator=(Shader&& shader) {
    if(this == &shader) {
        return *this;
    }
    if(shaderID != 0) {
        glDeleteShader(shaderID);
    }
    shaderID = shader.shaderID;
    shaderType = shader.shaderType;
    shader.shaderID = 0;
    shader.shaderType = GL_NONE;
    return *this;
}

GLuint Shader::getID() const {
    return shaderID;
}

GLuint Shader::getType() const {
    return shaderType;
}

bool Shader::isValid() const {
    return shaderID != 0;
}

Shader::~Shader() {
    if(shaderID != 0) {
        glDeleteShader(shaderID);
    }
}