#version 440 core

out vec4 theColor;

in vec2 textureCoord;

uniform sampler2D ourTexture;
uniform float visibility;

void main() {
  theColor = texture(ourTexture, textureCoord) * visibility;
}
