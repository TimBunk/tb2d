#version 440 core
in vec2 textureCoord;
in vec4 _color;

out vec4 crystal;

uniform sampler2D ourTexture;

void main() {
  crystal = texture(ourTexture, textureCoord);
  vec4 glow = crystal * _color;
  crystal += glow;
}
