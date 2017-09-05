#version 440 core
out vec4 color;
uniform vec4 ourColor;
uniform float green;
void main() {
color = vec4(1.0f, green, 0.0f, 1.0f);
//color = ourColor;
}
