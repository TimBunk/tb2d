#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "texture.h"
#include "shader.h"

#include <GL/glew.h>

class ResourceManager {
public:
	static void Destroy();

	// Example: CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	static void CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath);
	static Shader* GetShader(std::string name);

	// Example: CreateTexture("texture", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	static void CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter);
	static Texture* GetTexture(std::string name);

private:
	static ResourceManager* GetInstance();
	ResourceManager();
	~ResourceManager();

	static ResourceManager* rm;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture*> textures;
};

#endif // !RESOURCEMANGER_H
