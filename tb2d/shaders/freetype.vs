#version 440 core
layout (location = 0) in vec4 position;
layout (location = 1) in float textureID;
layout (location = 2) in vec3 color;
layout (location = 3) in mat4 model;

out VS_OUT
{
  vec2 textureCoord;
  float textureID;
  vec3 color;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f);

  vs_out.textureCoord = position.zw;
  vs_out.color = color;
  vs_out.textureID = textureID;
}
