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

QuadData ResourceManager::GetQuad(glm::vec2 pivot)
{
	ResourceManager* _rm = ResourceManager::GetInstance();
	CompareVectors2 _pivot = { pivot.x, pivot.y };
	// Search for an excisting quad
	if (_rm->quads.find(_pivot) != _rm->quads.end()) {
		std::cout << "Found a fitting quad" << std::endl;
		return _rm->quads[_pivot];
	}
	float vertices[] = {
		// position							// uv's
		-0.5f + pivot.x, 0.5f + pivot.y,	0.0f, 1.0f,  // uper left corner
		-0.5f + pivot.x, -0.5f + pivot.y,	0.0f, 0.0f,  // lower-left corner
		0.5f + pivot.x, -0.5f + pivot.y,	1.0f, 0.0f,  // lower-right corner

		0.5f + pivot.x, -0.5f + pivot.y,	1.0f, 0.0f,  // lower-right corner
		0.5f+ pivot.x, 0.5f + pivot.y,		1.0f, 1.0f,  // upper-right corner
		-0.5f + pivot.x, 0.5f + pivot.y,	0.0f, 1.0f,  // uper left corner
	};

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	std::cout << "Could not find the quad so we had to create a new one" << std::endl;
	QuadData qd = { VAO, VBO };
	_rm->quads[_pivot] = qd;
	return qd;
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
	// Delete VAO's and VBO's
	std::map<CompareVectors2, QuadData>::iterator it3 = quads.begin();
	while (it3 != quads.end()) {
		std::cout << "deleted quad" << std::endl;
		glDeleteVertexArrays(1, &(*it3).second.VAO);
		glDeleteBuffers(1, &(*it3).second.VBO);
		it3 = quads.erase(it3);
	}
}