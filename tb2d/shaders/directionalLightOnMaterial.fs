#version 440 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light
{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec3 fragPos;
in vec3 normal;
in vec2 textCoord;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
  // ambient
  vec3 ambient = light.ambient * material.ambient;

  // diffuse
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * material.diffuse;

  // specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * spec * material.specular;

  // final result
  vec3 result = (ambient + diffuse + specular);// * objectColor;
  color = vec4(result, 1.0f);
}
