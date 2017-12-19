#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in mat4 model;
layout (location = 5) in vec2 uv;
out vec2 textureCoord;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position, 0.0f, 1.0f);
  textureCoord = uv;
}