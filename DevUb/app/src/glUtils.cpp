#include "glUtils.hpp"

#include <cassert>
#include <fstream>
#include <iostream>

const float PI = 3.14159265f;

void CHECK_GL_STATUS(const char* place) {
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "[" << place << "] GL ERROR: " << gluErrorString(err) << std::endl;
    }
}

std::string getShaderLog(GLuint instanceID) {
    GLint tLogSize = 0;
    glGetShaderiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if (tLogSize <= 1) {
        return "?";
    }
    std::string tLogStr;
    tLogStr.resize(tLogSize);
    glGetShaderInfoLog(instanceID, tLogSize, nullptr, &tLogStr[0]);
    return tLogStr;
}

GLuint loadShader(const char* shaderPath, GLenum shaderType) {
    std::string errForStr = "";
    switch (shaderType) {
    case GL_VERTEX_SHADER:
        errForStr = "vertex";
        break;
    case GL_FRAGMENT_SHADER:
        errForStr = "fragment";
        break;
    default:
        assert(0 && "[GL Util] Invalid shader type");
        return 0;
    }
    std::ifstream fin(shaderPath);
    if (!fin.is_open()) {
        std::cerr << "[GL Util] Can't open " << errForStr << " shader file: \"" << shaderPath << "\"" << std::endl;
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
    if (compiled != GL_TRUE) {
        std::cerr << "[GL Util] Can't compile " << errForStr << " shader from file: \"" << shaderPath << "\"";
        std::cerr << "\n[GL Util] Problem: " << getShaderLog(shaderID) << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}

std::string getProgramLog(GLuint instanceID) {
    GLint tLogSize = 0;
    std::vector<GLchar> tLogBuffer;
    glGetProgramiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if (tLogSize <= 1) {
        return "?";
    }
    tLogBuffer.resize(tLogSize);
    glGetProgramInfoLog(instanceID, tLogSize, nullptr, &tLogBuffer[0]);
    return std::string(&tLogBuffer[0]);
}

GLuint linkProgram(GLuint vertID, GLuint fragID) {
    GLuint tProgID = glCreateProgram();
    glAttachShader(tProgID, vertID);
    glAttachShader(tProgID, fragID);
    glLinkProgram(tProgID);
    glDetachShader(tProgID, vertID);
    glDetachShader(tProgID, fragID);
    GLint linked = GL_FALSE;
    glGetProgramiv(tProgID, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE) {
        std::cerr << "[GL Util] Can't link program: " << getProgramLog(tProgID) << std::endl;
        glDeleteProgram(tProgID);
        return 0;
    }
    return tProgID;
}

GLDrawData createGLDraw(const char* vert, const char* frag, const std::vector<GLfloat>& vertList) {
    GLDrawData tDraw;
    GLuint vertShader = 0, fragShader = 0;
    vertShader = loadShader(vert, GL_VERTEX_SHADER);
    fragShader = loadShader(frag, GL_FRAGMENT_SHADER);
    if (vertShader == 0 || fragShader == 0) {
        // check which shader is not zero and delete
        return tDraw;
    }
    tDraw.progID = linkProgram(vertShader, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    if (tDraw.progID == 0) {
        return tDraw;
    }
    GLuint vaoID = 0, bufferID = 0;
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &bufferID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertList.size() * sizeof(GLfloat), &vertList[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    tDraw.vaoID = vaoID;
    tDraw.bufferID = bufferID;
    return tDraw;
}

std::vector<GLfloat> generateCircle(int sideCount) {
    std::vector<GLfloat> tVec;
    float tFract = 2.f * PI / (sideCount - 1);
    tVec.push_back(0.0f);
    tVec.push_back(0.0f);
    for (int i = 1; i <= sideCount; ++i) {
        float x = cos(tFract * i);
        float y = sin(tFract * i);
        tVec.push_back(x);
        tVec.push_back(y);
    }
    return tVec;
}