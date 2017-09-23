#version 440 core

out vec4 theColor;

in vec2 textureCoord;

//uniform vec4 color;
uniform sampler2D ourTexture;

void main() {
  //color = vec4(ourColor, 1.0f);
  theColor = texture(ourTexture, textureCoord);
  //color = texture(ourTexture, textureCoord);
  //theColor = color;
}
