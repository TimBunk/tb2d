#include "resourceManager.h"

ResourceManager* ResourceManager::rm = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (ResourceManager::rm == nullptr) {
		ResourceManager::rm = new ResourceManager();
		// The default shader
		ResourceManager::CreateShader("default", "shaders\\basic.vs", "shaders\\basic.fs");
		// The default freetype shader
		ResourceManager::CreateShader("defaultFreetype", "shaders\\defaultShader.vs", "shaders\\defaultFreetype.fs");
		// Debug Renderer
		ResourceManager::CreateShader("debugRenderer", "shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");
		// Debug Line Renderer
		ResourceManager::CreateShader("debugLineRenderer", "shaders\\debugLineRenderer.vs", "shaders\\debugLineRenderer.fs");
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

void ResourceManager::CreateTexture(std::string nameOfTexture, const char * filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter)
{
	Texture* texture;
	texture = new Texture(filePath, textureWrap, textureFilter, mipmapFilter);
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