#version 330 core

in vec3 fFragPos;
in vec3 fNormal;

out vec4 fragColor;

uniform vec3 ViewPos;
uniform vec3 LightPos;
uniform vec4 LightColor;
uniform vec4 FragColor;

vec4 calcSpecular(in vec3 lightDir) {
  float specStr = 0.5f;
  vec3 viewDir = normalize(ViewPos - fFragPos);
  vec3 reflectDir = reflect(-lightDir, fNormal);
  float specVal = pow(max(dot(viewDir, reflectDir), 0.f), 16);
  return specStr * specVal * LightColor;
}

vec4 calcDiffuse(in vec3 lightDir) {
  float diff = max(dot(fNormal, lightDir), 0.f);
  return diff * LightColor;
}

vec4 calcAmbient() {
  float ambientStr = 0.1f;
  return ambientStr * LightColor;
}

void main() {
  vec3 lightDir = normalize(LightPos - fFragPos);
  fragColor = (calcAmbient() +  calcDiffuse(lightDir) + calcSpecular(lightDir)) * FragColor;
}