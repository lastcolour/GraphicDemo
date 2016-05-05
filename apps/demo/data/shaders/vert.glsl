#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 transform;

void main() {
  gl_Position = transform * vec4(vPosition, 1.0f);
  texCoord = vTexCoord;
  color = vec4(vColor, 1.0);
}