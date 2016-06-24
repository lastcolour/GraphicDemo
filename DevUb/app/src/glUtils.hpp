#ifndef __GL_UTILS_HPP__
#define __GL_UTILS_HPP__

#include "GLDraw.hpp"

#include <GL/glew.h>
#include <vector>
#include <string>

void CHECK_GL_STATUS(const char* place);

std::string getProgramLog(GLuint instanceID);

std::string getShaderLog(GLuint instanceID);

GLuint loadShader(const char* shaderPath, GLenum shaderType);

GLuint linkProgram(GLuint vertID, GLuint fragID);

std::vector<GLfloat> generateCircle(int Points);

GLDrawData createGLDraw(const char* vert, const char* frag, const std::vector<GLfloat>& vertList);

std::vector<GLfloat> generateCircle(int sideCount);

#endif /* __GL_UTILS_HPP__ */
