#version 330 core

uniform float vRadius;
uniform vec2 vCenter;

layout(location = 0) in vec2 vPosition;

void main() {
  gl_Position = vec4(vPosition * vRadius + vCenter, 0.0, 1.0);
}