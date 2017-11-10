#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "texture.h"
#include "shader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class ResourceManager {
public:
	ResourceManager();
	virtual ~ResourceManager();

	Shader* GetShader(std::string name);
	Texture GetTexture(std::string name);

	// Example: CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	void CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath);
	// Example: CreateTexture("texture", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	void CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType);

private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture> textures;
};

#endif // !RESOURCEMANGER_H
