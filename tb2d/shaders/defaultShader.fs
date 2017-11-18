#version 440 core
in vec2 textureCoord;
out vec4 color;

uniform sampler2D ourTexture;

void main() {
  color = texture(ourTexture, textureCoord);
}
