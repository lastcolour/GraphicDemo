// author: Oleksii Zhogan (alexzhogan@gmail.com)

#include <openGL/ShaderProgram.hpp>

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

std::string getProgramLog(GLuint instanceID) {
    GLint tLogSize = 0;
    std::vector<GLchar> tLogBuffer;
    glGetProgramiv(instanceID, GL_INFO_LOG_LENGTH, &tLogSize);
    if(tLogSize <= 1) {
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
    if(linked != GL_TRUE) {
        std::cerr << "[ShaderProgram] Can't link program: " << getProgramLog(tProgID) << std::endl;
        glDeleteProgram(tProgID);
        return 0;
    }
    return tProgID;
}

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

ShaderProgram::ShaderProgram(GLuint vertID, GLuint fragID) : OpenGLObject() {
    assert(vertID != 0 && "Invalid vertex program id");
    assert(fragID != 0 && "Invalid fragment program id");
    GLuint tProgID = linkProgram(vertID, fragID);
    if(tProgID != 0) {
        holdID(tProgID);
    }
}

ShaderProgram::ShaderProgram(const char* vertShader, const char* fragShader) {
    Shader tVert(vertShader, GL_VERTEX_SHADER);
    Shader tFrag(fragShader, GL_FRAGMENT_SHADER);
    assert(tVert.getID() != 0 && "Invalid vertex program id");
    assert(tFrag.getID() != 0 && "Invalid fragment program id");
    if(tVert.getID() == 0 || tFrag.getID() == 0) {
        return;
    }
    GLuint tProgID = linkProgram(tVert.getID(), tFrag.getID());
    if(tProgID != 0) {
        holdID(tProgID);
    }
}

ShaderProgram::ShaderProgram(const Shader& firstShader, const Shader& secondShader) :
    OpenGLObject() {
    assert(firstShader.getID() != 0 && "Invalid vertex program id");
    assert(secondShader.getID() != 0 && "Invalid fragment program id");
    GLuint vertID = 0;
    GLuint fragID = 0;
    if(firstShader.getType() != secondShader.getType()) {
        vertID = firstShader.getType() == GL_VERTEX_SHADER ? firstShader.getID() : secondShader.getID();
        fragID = firstShader.getType() == GL_FRAGMENT_SHADER ? firstShader.getID() : secondShader.getID();
    }
    assert(vertID != 0 && "No vertex shader specified");
    assert(fragID != 0 && "No fragment shader specified");
    GLuint tProgID = linkProgram(vertID, fragID);
    if(tProgID != 0) {
        holdID(tProgID);
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& program) {
    replaceID(std::move(program));
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& program) {
    if(this == &program) {
        return *this;
    }
    replaceID(std::move(program));
    return *this;
}

ShaderProgram::~ShaderProgram() {
    if(makeIsBoundCheck(getID())) {
        makeUnbind(getID());
    }
    makeFree(getID());
}

void ShaderProgram::setUniform1f(const char* name, float x) const {
    assert(getID() != 0 && "Invalid shader program used");
    GLint unifLoc = -1;
    glUseProgram(getID());
    if((unifLoc = getUniformLocation(name)) != -1) {
        glUniform1f(unifLoc, x);
    }
    glUseProgram(0);
}

void ShaderProgram::setUniform4f(const char* name, float x, float y, float z, float w) const {
    assert(getID() != 0 && "Invalid shader program used");
    GLint unifLoc = -1;
    glUseProgram(getID());
    if((unifLoc = getUniformLocation(name)) != -1) {
        glUniform4f(unifLoc, x, y, z, w);
    }
    glUseProgram(0);
}

bool ShaderProgram::makeIsBoundCheck(GLuint resourceID) {
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    return resourceID == tProgram;
}

bool ShaderProgram::makeCheck(GLuint resourceID) {
    return resourceID != 0;
}

bool ShaderProgram::makeBind(GLuint resourceID) {
    glUseProgram(resourceID);
    return true;
}

bool ShaderProgram::makeUnbind(GLuint resourceID) {
    glUseProgram(0);
    return true;
}

bool ShaderProgram::makeFree(GLuint resourceID) {
    glDeleteProgram(resourceID);
    return true;
}

GLint ShaderProgram::getUniformLocation(const char* name) const {
    assert(getID() != 0 && "Invalid shader program used");
#ifdef GD_CORE_LIB_DEBUG
    GLint tProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &tProgram);
    assert(tProgram == getID() && "Set uniform for not bounded program");
#endif

    GLint unifLoc = glGetUniformLocation(getID(), name);

#ifdef GD_CORE_LIB_DEBUG
    if(unifLoc == -1) {
        reportUniformNameError(name);
    }
#endif
    return unifLoc;
}

void ShaderProgram::reportUniformNameError(const char* name) const {
    std::vector<std::string> allUniforms = getAllUniformsNames(getID());
    std::string tMessagePrefix;
    tMessagePrefix = tMessagePrefix + "[ShaderProgram:" + std::to_string(getID()) + "] ";
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
