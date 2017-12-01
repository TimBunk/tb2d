#version 440 core
in vec2 textureCoord;
out vec4 color;

uniform sampler2D ourTexture;
uniform vec4 glow;

void main() {
  color = texture(ourTexture, textureCoord);
  color += glow;
}
