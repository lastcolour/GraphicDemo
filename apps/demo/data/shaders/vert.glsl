#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;

out vec2 texCoord;

uniform mat4 ModelView;
uniform mat4 Projection;

void main() {
  gl_Position = Projection * ModelView * vec4(vPosition, 1.f);
  texCoord = vTexCoord;
}