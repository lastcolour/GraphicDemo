#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec4 resColor;

void main() {
  gl_Position = vec4(vPosition, 1.0f);
  resColor = vec4(vColor, 1.0f);
}

