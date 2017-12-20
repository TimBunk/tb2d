#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in mat4 model;
layout (location = 5) in vec2 uv;
layout (location = 6) in vec4 color;

out vec2 textureCoord;
out vec4 _color;

uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
  textureCoord = uv;
  _color = color;
}
