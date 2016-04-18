#include <openGL/ShaderProgram.hpp>

#include <assert.h>
#include <fstream>
#include <iostream>


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
	}
	std::ifstream fin(shaderPath);
	if(!fin.is_open()) {
		std::cerr << "[ShaderProgram] Can't open "  << errForStr << " shader file: " << shaderPath << std::endl;
		return 0;
	}
	std::string shaderStr;
	std::copy(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), shaderStr.begin());
	GLuint shaderID = glCreateShader(shaderType);
	const GLchar* vShaderCode = shaderStr.c_str();
	glShaderSource(shaderID, 1, &vShaderCode, nullptr);
	glCompileShader(shaderID);
	GLint compiled = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if(compiled != GL_TRUE) {
		std::cerr << "[ShaderProgram] Can't compile " << errForStr << " shader from file: " << shaderPath;
		std::cerr << "[ShaderProgram] Problem: " << getInfoLog(shaderID) << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}
	return shaderID;
}


ShaderProgram::ShaderProgram(const std::string& vertShaderPath, const std::string& fragShaderPath) :
		programID(0) {
	// TODO: Make this constructor private and public static method to class ShaderProgram::createProgram()
	//       that create program step by step
	GLuint vertID = loadShader(vertShaderPath, GL_VERTEX_SHADER);
	GLuint fragID = loadShader(fragShaderPath, GL_FRAGMENT_SHADER);
	if(!vertID || !fragID) {
		return;
	}
    programID = glCreateProgram();
    glAttachShader(programID, vertID);
    glAttachShader(programID, fragID);
    glLinkProgram(programID);
    GLint linked = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if(!linked) {
		std::cerr << "[ShaderProgram] Can't link program from:"
				  << "\n - Vertex  : " << vertShaderPath
				  << "\n - Fragment: " << fragShaderPath;
		std::cerr << "[ShaderProgram] Problem: " << getInfoLog(programID, true) << std::endl;
		glDeleteShader(programID);
		programID = 0;
    }
    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

ShaderProgram::~ShaderProgram() {
	if(programID) {
		glDeleteProgram(0);
	}
}

void ShaderProgram::bind() {
	glUseProgram(programID);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

bool ShaderProgram::isComplete() {
	return programID == 0;
}
