#version 330

layout(location = 0) in vec4 position;
layout(location = 0) in vec4 color;

out fragColor;

void main() {
  gl_Position = position;
  fragColor = color;
}

