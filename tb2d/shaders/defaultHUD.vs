#version 440 core
layout (location = 0) in vec4 position;
out vec2 textureCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
  gl_Position = projection * model * vec4(position.xy, 0.0f, 1.0f);
  textureCoord = position.zw;
}
