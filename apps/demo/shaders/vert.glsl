#version 330 core

layout(location = 0) in vec3 vPosition;

uniform float hOffset;

void main() {
  gl_Position = vec4(vPosition.x + hOffset, vPosition.y, vPosition.z, 1.0f);
}