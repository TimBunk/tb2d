#version 440 core

struct Material {
  uint diffuseMaps;
  sampler2D diffuse[10];
  uint specularMaps;
  sampler2D specular[10];
  uint emissionMaps;
  sampler2D emission[10];
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
uniform float visibility;

void main() {
  // setup variables
  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);
  vec3 emission = vec3(0.0f);

  // diffuse calculation
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0f);
  // ambient and diffuse
  for (int i = 0;i<material.diffuseMaps;i++) {
    ambient += light.ambient * vec3(texture(material.diffuse[i], textCoord));
    diffuse += light.diffuse * diff * vec3(texture(material.diffuse[i], textCoord));
  }
  // specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  for (int i = 0;i<material.specularMaps;i++) {
    specular += light.specular * spec * vec3(texture(material.specular[i], textCoord));
  }
  // emission
  for (int i =0;i<material.emissionMaps;i++) {
    emission += vec3(texture(material.emission[i], textCoord) * visibility);
  }
  // final result
  vec3 result = (ambient + diffuse + specular + emission);
  color = vec4(result, 1.0f);
}
