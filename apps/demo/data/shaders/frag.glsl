#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D Smile;
uniform sampler2D Container;

void main() {
  vec4 texel0, texel1;
  texel0 = texture(Container, texCoord);
  texel1 = texture(Smile, texCoord);
  fragColor = mix(texel0, texel1, 0.2f);
}
