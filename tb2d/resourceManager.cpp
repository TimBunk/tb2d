#include "resourceManager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
	std::map<std::string, Shader*>::iterator it = shaders.begin();
	while (it != shaders.end()) {
		it = shaders.erase(it);
	}
}

Shader* ResourceManager::GetShader(std::string name) {
	// Search for an excisting shader that has already been loaded once
	if (shaders.find(name) != shaders.end()) {
		return shaders[name];
	}
	std::cout << "ResourceManager could not find the shader: " << name << std::endl;
 	return NULL;
}

Texture ResourceManager::GetTexture(std::string name) {
	// Search for an excisting texture that has already been loaded once
	if (textures.find(name) != textures.end()) {
		return textures[name];
	}
	std::cout << "ResourceManager could not find the texture: " << name << std::endl;
	Texture texture;
	texture.id = NULL;
	texture.type = "NULL";
	return texture;
}

void ResourceManager::CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath) {
	Shader* shader;
	shader = new Shader(vertexPath, fragmentPath);
	shaders[nameOfShader] = shader;
}

void ResourceManager::CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType) {
	Texture texture;
	texture = Tex::LoadTexture(filePath, textureWrap, textureFilter, textureType);
	textures[nameOfTexture] = texture;
}
