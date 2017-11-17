#include "resourceManager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
	// Delete shaders
	std::map<std::string, Shader*>::iterator it = shaders.begin();
	while (it != shaders.end()) {
		delete (*it).second;
		it = shaders.erase(it);
	}
	// Delete textures
	std::map<std::string, Texture*>::iterator it2 = textures.begin();
	while (it2 != textures.end()) {
		delete (*it2).second;
		it2 = textures.erase(it2);
	}
}

Shader* ResourceManager::GetShader(std::string name) {
	// Search for an excisting shader that has already been loaded once
	if (shaders.find(name) != shaders.end()) {
		return shaders[name];
	}
	std::cout << "ResourceManager could not find the shader: " << name << std::endl;
 	return nullptr;
}

Texture* ResourceManager::GetTexture(std::string name) {
	// Search for an excisting texture that has already been loaded once
	if (textures.find(name) != textures.end()) {
		return textures[name];
	}
	std::cout << "ResourceManager could not find the texture: " << name << std::endl;
	return nullptr;
}

void ResourceManager::CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath) {
	Shader* shader;
	shader = new Shader(vertexPath, fragmentPath);
	shaders[nameOfShader] = shader;
}

void ResourceManager::CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType) {
	Texture* texture;
	texture = new Texture(filePath, textureWrap, textureFilter, textureType);
	textures[nameOfTexture] = texture;
}
