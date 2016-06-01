#version 330 core

layout(location = 0) in vec3 vPosition;

uniform mat4 TransformMat;
uniform mat4 CameraMat;

void main() {
  gl_Position = CameraMat * TransformMat * vec4(vPosition, 1.f);
}