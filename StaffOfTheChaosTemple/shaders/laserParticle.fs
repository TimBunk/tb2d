#version 440 core

in VS_OUT
{
  vec2 textureCoord;
  float textureID;
  vec4 color;
} fs_in;

out vec4 color;

uniform sampler2D textures[32];

void main() {
  if (fs_in.textureID > 0.0) {
    int tID = int(fs_in.textureID);
    tID -= 1;
    color = texture(textures[tID], fs_in.textureCoord);
    color = vec4(color.r + fs_in.color.r, color.g + fs_in.color.g, color.b + fs_in.color.b, color.a * fs_in.color.a);
  }
  else {
    color = fs_in.color;
  }
}
