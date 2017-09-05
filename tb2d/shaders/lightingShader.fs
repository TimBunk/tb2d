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

// directionalLight
struct DirLight
{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

// pointLight
struct PointLight
{
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// spotLight
struct SpotLight
{
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

in vec3 fragPos;
in vec3 normal;
in vec2 textCoord;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform uint amountOfPointLights;
uniform PointLight pointLight[40];
uniform SpotLight spotLight;
uniform float visibility;

void main() {
  // initialize some usefull variables
  vec3 emission = vec3(0.0f);
  vec3 result = vec3(0.0f);
  vec3 norm = normalize(normal);
  vec3 viewDir = normalize(viewPos - fragPos);

  // add the directionalLight to the result
  result = CalcDirLight(dirLight, norm, viewDir);
  // add the pointLights to the result
  for (int i=0;i<amountOfPointLights;i++) {
    result += CalcPointLight(pointLight[i], norm, fragPos, viewDir);
  }
  // add the spotLight to the result
  result += CalcSpotLight(spotLight, norm, fragPos, viewDir);

  // add the emissionMaps
  for (int i =0;i<material.emissionMaps;i++) {
    result += vec3(texture(material.emission[i], textCoord) * visibility);
  }
  // result
  color = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);

  vec3 lightDir = normalize(-light.direction);
  vec3 reflectDir = reflect(-lightDir, normal);

  // diffuse
  float diff = max(dot(normal, lightDir), 0.0f);

  // specular
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

  // result
  for (int i = 0;i<material.diffuseMaps;i++) {
    ambient += light.ambient * vec3(texture(material.diffuse[i], textCoord));
    diffuse += light.diffuse * diff * vec3(texture(material.diffuse[i], textCoord));
  }
  for (int i = 0;i<material.specularMaps;i++) {
    specular += light.specular * spec * vec3(texture(material.specular[i], textCoord));
  }
  return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);

  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse
  float diff = max(dot(normal, lightDir), 0.0f);
  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

  for (int i = 0;i<material.diffuseMaps;i++) {
    ambient += light.ambient * vec3(texture(material.diffuse[i], textCoord));
    diffuse += light.diffuse * diff * vec3(texture(material.diffuse[i], textCoord));
  }
  for (int i = 0;i<material.specularMaps;i++) {
    specular += light.specular * spec * vec3(texture(material.specular[i], textCoord));
  }
  // calculation for the light intensity over distance
  float _distance = length(light.position - fragPos);
  float attentuation = 1.0f / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));

  // result
  ambient *= attentuation;
  diffuse *= attentuation;
  specular *= attentuation;
  return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 ambient = vec3(0.0f);
  vec3 diffuse = vec3(0.0f);
  vec3 specular = vec3(0.0f);

  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0f);

  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

  for (int i = 0;i<material.diffuseMaps;i++) {
    ambient += light.ambient * vec3(texture(material.diffuse[i], textCoord));
    diffuse += light.diffuse * diff * vec3(texture(material.diffuse[i], textCoord));
  }
  for (int i = 0;i<material.specularMaps;i++) {
    specular += light.specular * spec * vec3(texture(material.specular[i], textCoord));
  }
  // calculation for the light intensity over distance
  float _distance = length(light.position - fragPos);
  float attentuation = 1.0f / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));

  // calculate the intensity between the cutOff and the outerCutOff
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

  // result
  diffuse *= intensity * attentuation;
  specular *= intensity * attentuation;
  return (ambient + diffuse + specular);
}
