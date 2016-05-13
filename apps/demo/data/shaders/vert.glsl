#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;

out vec2 texCoord;

uniform mat4 WorldMat;
uniform mat4 CameraMat;

void main() {
  gl_Position = CameraMat * WorldMat * vec4(vPosition, 1.f);
  texCoord = vTexCoord;
}