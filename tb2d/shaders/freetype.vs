#version 440 core
layout (location = 0) in vec2 vertex; // <vec2 pos>
layout (location = 1) in vec2 textureCoordinate; // <vec2 text>
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0f, 1.0f);
    texCoords = textureCoordinate;
}
