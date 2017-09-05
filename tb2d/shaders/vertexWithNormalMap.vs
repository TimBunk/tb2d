#version 440 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;
out vec2 textCoord;
out mat3 TBN;

void main() {
  gl_Position = projection * view * transform * vec4(position, 1.0f);
  fragPos = vec3(transform * vec4(position, 1.0f));
  normal = mat3(transpose(inverse(transform))) * aNormal;
  //textCoord = textureCoord;
  textCoord = vec2(textureCoord.x, 1-textureCoord.y);

  vec3 T = normalize(vec3(transform * vec4(aTangent, 0.0f)));
  vec3 B = normalize(vec3(transform * vec4(aBitangent, 0.0f)));
  vec3 N = normalize(vec3(transform * vec4(aNormal, 0.0f)));
  // TangentBigtangentNormal
  TBN = mat3(T, B, N);
}
