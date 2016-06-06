#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 fFragPos;
out vec3 fNormal;

uniform mat4 CameraMat;
//uniform mat4 WorldMat;

void main() {
  gl_Position = CameraMat  * vec4(vPosition, 1.f);
  fFragPos = vPosition;
  fNormal = vNormal;
}