#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in mat4 model;

out vec3 theColor;

uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
  theColor = color;
}
