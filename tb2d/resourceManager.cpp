#include "resourceManager.h"

ResourceManager* ResourceManager::rm = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (ResourceManager::rm == nullptr) {
		ResourceManager::rm = new ResourceManager();
		// The default shader
		ResourceManager::CreateShader("defaultShader", "shaders\\defaultShader.vs", "shaders\\defaultShader.fs");
		// The default HUD shader
		ResourceManager::CreateShader("defaultHUD", "shaders\\defaultHUD.vs", "shaders\\defaultShader.fs");
		// The default freetype shader
		ResourceManager::CreateShader("defaultFreetype", "shaders\\defaultFreetype.vs", "shaders\\defaultFreetype.fs");
		// The default freetypeHUD shader
		ResourceManager::CreateShader("defaultFreetypeHUD", "shaders\\defaultFreetypeHUD.vs", "shaders\\defaultFreetype.fs");
		// The color shader
		ResourceManager::CreateShader("color", "shaders\\color.vs", "shaders\\color.fs");
		// The colorHUD shader
		ResourceManager::CreateShader("colorHUD", "shaders\\colorHUD.vs", "shaders\\colorHUD.fs");
	}
	return ResourceManager::rm;
}

void ResourceManager::Destroy()
{
	if (ResourceManager::rm != nullptr) {
		delete ResourceManager::rm;
		ResourceManager::rm = nullptr;
	}
}

void ResourceManager::CreateShader(std::string nameOfShader, const char * vertexPath, const char * fragmentPath)
{
	Shader* shader;
	shader = new Shader(vertexPath, fragmentPath);
	ResourceManager::GetInstance()->shaders[nameOfShader] = shader;
}

Shader * ResourceManager::GetShader(std::string name)
{
	ResourceManager* _rm = ResourceManager::GetInstance();
	// Search for an excisting shader that has already been loaded once
	if (_rm->shaders.find(name) != _rm->shaders.end()) {
		return _rm->shaders[name];
	}
	std::cout << "ResourceManager could not find the shader: " << name << std::endl;
	return nullptr;
}

void ResourceManager::CreateTexture(std::string nameOfTexture, const char * filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType)
{
	Texture* texture;
	texture = new Texture(filePath, textureWrap, textureFilter, textureType);
	ResourceManager::GetInstance()->textures[nameOfTexture] = texture;
}

Texture * ResourceManager::GetTexture(std::string name)
{
	ResourceManager* _rm = ResourceManager::GetInstance();
	// Search for an excisting texture that has already been loaded once
	if (_rm->textures.find(name) != _rm->textures.end()) {
		return _rm->textures[name];
	}
	std::cout << "ResourceManager could not find the texture: " << name << std::endl;
	return nullptr;
}

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{
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