#version 440 core
layout (location = 0) in vec3 vertex; // <vec3 pos>
layout (location = 1) in vec2 textureCoordinates; // <vec2 text>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xyz, 1.0);
    TexCoords = textureCoordinates;
}
