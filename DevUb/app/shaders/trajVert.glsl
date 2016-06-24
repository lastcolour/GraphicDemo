#version 330 core

uniform float vAngle;
uniform float vSize;
uniform vec2  vCenter;

layout(location = 0) in vec2 vPosition;

void main() {
  // rotate
  vec2 tVec = vec2();
  tVec.x = vPosition.x * cos(vAngle) - vPosition.y * sin(vAngle);
  tVec.y = vPosition.y * cos(vAngle) + vPosition.x * sin(vAngle);
  // scale
  //tVec = vPosition * vSize;
  // translate
  tVec = tVec + vCenter;
  gl_Position = vec4(tVec, 0.0, 1.0);
}