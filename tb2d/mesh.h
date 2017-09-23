#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <Box2D/Box2D.h>

#include "shader.h"
#include "texture.h"

struct MeshData {
	GLfloat* vertices;
	b2Vec2* b2Vertices;
	int32 amountVertices;
	bool hasTextCoord;
};

class Mesh {

public:

	Mesh(MeshData meshData);
	~Mesh();

	void DrawTextures(Shader* shader);
	void Draw();

	void SetAmountOfTextures(unsigned int diffuseMaps, unsigned int specularMaps, unsigned int emissionMaps);
	void AddTexture(Texture texture);

private:
	unsigned int amountVertices;
	GLuint VBO, VAO;

	unsigned int diffuseMaps, specularMaps, emissionMaps;
	std::vector<Texture> textures;
};

#endif // !MESH_H
