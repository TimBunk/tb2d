#include "resourceManager.h"

ResourceManager* ResourceManager::rm = nullptr;

void ResourceManager::Initialize()
{
	if (ResourceManager::rm == nullptr) {
		ResourceManager::rm = new ResourceManager();
		// The default shader
		CreateShader("default", "shaders\\basic.vs", "shaders\\basic.fs");
		// The default freetype shader
		CreateShader("freetype", "shaders\\freetype.vs", "shaders\\freetype.fs");
		// Debug Renderer shader
		CreateShader("debugRenderer", "shaders\\debugRenderer.vs", "shaders\\debugRenderer.fs");
		// Debug Line Renderer shader
		CreateShader("debugLineRenderer", "shaders\\debugLineRenderer.vs", "shaders\\debugLineRenderer.fs");
	}
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
	ResourceManager::rm->shaders[nameOfShader] = shader;
}

Shader * ResourceManager::GetShader(std::string name)
{
	// Search for an excisting shader that has already been loaded once
	if (ResourceManager::rm->shaders.find(name) != ResourceManager::rm->shaders.end()) {
		return ResourceManager::rm->shaders[name];
	}
	std::cout << "ResourceManager could not find the shader: " << name << std::endl;
	return nullptr;
}

void ResourceManager::CreateTexture(std::string nameOfTexture, const char * filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter)
{
	Texture* texture;
	texture = new Texture(filePath, textureWrap, textureFilter, mipmapFilter);
	ResourceManager::rm->textures[nameOfTexture] = texture;
}

Texture * ResourceManager::GetTexture(std::string name)
{
	// Search for an excisting texture that has already been loaded once
	if (ResourceManager::rm->textures.find(name) != ResourceManager::rm->textures.end()) {
		return ResourceManager::rm->textures[name];
	}
	std::cout << "ResourceManager could not find the texture: " << name << std::endl;
	return nullptr;
}

Font ResourceManager::GetFont(std::string filePath, int textureAtlasSize, int fontSize)
{
	if (ResourceManager::rm->fonts.find(filePath) != ResourceManager::rm->fonts.end()) {
		if (ResourceManager::rm->fonts[filePath].find(fontSize) != ResourceManager::rm->fonts[filePath].end()) {
			if (ResourceManager::rm->fonts[filePath][fontSize].find(textureAtlasSize) != ResourceManager::rm->fonts[filePath][fontSize].end()) {
				return ResourceManager::rm->fonts[filePath][fontSize][textureAtlasSize];
			}
		}
	}
	// If no existing font was found create a new one and return it
	Font font;
	font.textureAtlas = texture_atlas_new(textureAtlasSize, textureAtlasSize, 1);
	font.font = texture_font_new_from_file(font.textureAtlas, fontSize, filePath.c_str());

	for (int a = 0; a<256; ++a)
	{
		char b = (char)a;
		const char* c = &b;
		texture_font_get_glyph(font.font, c);
	}
	glGenTextures(1, &font.textureAtlas->id); glBindTexture(GL_TEXTURE_2D, font.textureAtlas->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font.textureAtlas->width, font.textureAtlas->height, 0, GL_RED, GL_UNSIGNED_BYTE, font.textureAtlas->data);

	ResourceManager::rm->fonts[filePath][fontSize][textureAtlasSize] = font;

	return font;
}

ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{
	// Delete shaders
	std::map<std::string, Shader*>::iterator itShader = shaders.begin();
	while (itShader != shaders.end()) {
		delete (*itShader).second;
		itShader = shaders.erase(itShader);
	}
	// Delete textures
	std::map<std::string, Texture*>::iterator itTexture = textures.begin();
	while (itTexture != textures.end()) {
		delete (*itTexture).second;
		itTexture = textures.erase(itTexture);
	}
	// Delete fonts
	for (std::map<std::string, std::map<int, std::map<int, Font>>>::iterator itFont = fonts.begin(); itFont != fonts.end(); ++itFont) {
		for (std::map<int, std::map<int, Font>>::iterator itFont2 = (*itFont).second.begin(); itFont2 != (*itFont).second.end(); ++itFont2) {
			std::map<int, Font>::iterator itFont3 = (*itFont2).second.begin();
			while (itFont3 != (*itFont2).second.end()) {
				glDeleteTextures(1, &(*itFont3).second.textureAtlas->id);
				texture_atlas_delete((*itFont3).second.textureAtlas);
				texture_font_delete((*itFont3).second.font);
				itFont3 = (*itFont2).second.erase(itFont3);
			}
		}
	}
}