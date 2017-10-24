#version 440 core

out vec4 theColor;

in vec2 textureCoord;

//uniform vec4 color;
uniform sampler2D ourTexture;
uniform vec4 color;

void main() {
  theColor = texture(ourTexture, textureCoord);
  theColor.r += color.r;
}
