#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "texture.h"
#include "shader.h"

#include <GL/glew.h>

struct CompareVectors2 {
	float x = 0.0f;
	float y = 0.0f;
	// Compare a vector two and check if it is lower than
	bool operator<(const CompareVectors2& rhs) const
	{
		if (x < rhs.x)
		{
			return true;
		}
		else if (x == rhs.x)
		{
			if (y < rhs.y)
			{
				return true;
			}
		}
		return false;
	}
};

struct QuadData {
	GLuint VAO = 0;
	GLuint VBO = 0;
};

class ResourceManager {
public:
	static void Destroy();

	// Example: CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	static void CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath);
	static Shader* GetShader(std::string name);

	// Example: CreateTexture("texture", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	static void CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter);
	static Texture* GetTexture(std::string name);

	// NOTE the vertices are in a normalized space. The pivot point is by default at the center.
	// Example to set pivot point in the top left: glm::vec2(-0.5f, 0.5f)
	static QuadData GetQuad(glm::vec2 pivot);

private:
	static ResourceManager* GetInstance();
	ResourceManager();
	~ResourceManager();

	static ResourceManager* rm;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture*> textures;
	std::map<CompareVectors2, QuadData> quads;
};

#endif // !RESOURCEMANGER_H
