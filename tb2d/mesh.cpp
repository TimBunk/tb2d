#include "mesh.h"
#include "OBJloader.h"

Mesh::Mesh(MeshData meshData)
{
	// initialize the needed variables
	unsigned int offset = 0;
	unsigned int multiplier = 3;
	// check if it has textureCoordinates
	if (meshData.hasTextCoord) {
		multiplier += 2;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, meshData.amountVertices * sizeof(GLfloat), &meshData.vertices[0], GL_STATIC_DRAW);
	// set the vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid*)offset);
	glEnableVertexAttribArray(0);
	offset += 3;
	// set the textCoordinates
	if (meshData.hasTextCoord) {
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
	this->amountVertices = (meshData.amountVertices/multiplier);
	//delete meshData.vertices;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::DrawTextures(Shader * shader)
{
	// bind the correct texture to the shaders
	unsigned int diffuseCount = 0;
	shader->SetUnsignedInt("material.diffuseMaps", diffuseMaps);
	unsigned int specularCount = 0;
	shader->SetUnsignedInt("material.specularMaps", specularMaps);
	unsigned int emissionCount = 0;
	shader->SetUnsignedInt("material.emissionMaps", emissionMaps);
	unsigned int texturesSize = textures.size();
	for (unsigned int i = 0; i < texturesSize; i++) {
		glActiveTexture(GL_TEXTURE1 + i);
		std::stringstream ss;
		std::string number;
		std::string name = textures[i].type;
		if (name == "diffuse") {
			ss << diffuseCount++; // NOTE to self: In this case C++ the increment call: variable++ returns the variable as is and then increments the variable 
		}
		else if (name == "specular") {
			ss << specularCount++;
		}
		else if (name == "emission") {
			ss << emissionCount++;
		}
		else if (name == "normalMap") {
			shader->SetInt(("material." + name).c_str(), textures[i].id);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			continue;
		}
		number = ss.str();
		shader->SetInt(("material." + name + "[" + number + "]").c_str(), textures[i].id);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	Draw();
	// Set everything back to default once configured
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, amountVertices);
	// Set everything back to default once configured
	glBindVertexArray(0);
}

void Mesh::SetAmountOfTextures(unsigned int diffuseMaps, unsigned int specularMaps, unsigned int emissionMaps)
{
	this->diffuseMaps = diffuseMaps;
	this->specularMaps = specularMaps;
	this->emissionMaps = emissionMaps;
}

void Mesh::AddTexture(Texture texture)
{
	textures.push_back(texture);
}
