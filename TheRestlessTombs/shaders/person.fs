#version 440 core

out vec4 theColor;

in vec2 textureCoord;

//uniform vec4 color;
uniform sampler2D ourTexture;
uniform float red;

void main() {
  theColor = texture(ourTexture, textureCoord);
  theColor.r += red;
}
