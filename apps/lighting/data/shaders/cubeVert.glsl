#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 fFragPos;
out vec3 fNormal;

uniform mat4 CameraMat;
uniform mat4 WorldMat;

void main() {
  vec4 fFragPos = WorldMat * vec4(vPosition, 1.f);
  gl_Position = CameraMat * fFragPos;
  fNormal = vNormal;
}