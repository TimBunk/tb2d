#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 textCoord;
out vec2 textureCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
  gl_Position = projection * model * vec4(position.xy, 0.0f, 1.0f);
  textureCoord = textCoord;
}
