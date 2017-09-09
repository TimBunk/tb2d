#version 440 core

out vec4 theColor;

uniform vec4 color;

void main() {
  theColor = color;
}
