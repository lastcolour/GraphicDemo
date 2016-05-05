#version 330 core

in vec4 color;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D Container;

void main() {
  fragColor = texture(Container, texCoord) * color;
}
