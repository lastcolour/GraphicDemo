#version 330 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D TextureUnit;

void main() {
  fragColor = texture(TextureUnit, texCoord);
  fragColor.a = 1.0;
}
