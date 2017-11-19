#version 440 core

out vec4 theColor;

uniform vec3 color;

void main() {
  theColor = vec4(color.xyz, 1.0f);
}
