#version 440 core

in VS_OUT
{
  vec2 textureCoord;
  float textureID;
  vec3 color;
} fs_in;

out vec4 color;

uniform sampler2D textures[32];

void main() {
  int tID = int(fs_in.textureID);
  tID -= 1;
  vec4 tex = texture(textures[tID], fs_in.textureCoord);
  color = vec4(fs_in.color, tex.r);
}
