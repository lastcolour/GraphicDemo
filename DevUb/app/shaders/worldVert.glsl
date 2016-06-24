#version 330 core

uniform float vSize;

layout(location = 0) in vec2 vPosition;

void main() {
  // scale
  vec2 tVec = vec2(clamp(vPosition.x, vSize, -1.0), clamp(vPosition.y, vSize, -1.0));
  gl_Position = vec4(tVec, 0.0, 1.0);
}