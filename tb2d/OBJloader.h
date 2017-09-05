#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <gl\glew.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <Box2D\Box2D.h>

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "mesh.h"

class OBJloader {

public:

	static MeshData LoadObject(const char* fileName, bool hasTextCoord);

private:

	static void LoadVertices(std::ifstream& obj, char* reader, std::vector<glm::vec3>& tmp_vertices);
	static void LoadTextures(std::ifstream& obj, char* reader, std::vector<glm::vec2>& tmp_textures);

	// this function loads faces with vertices and textures
	static void LoadFaces(std::ifstream& obj, char* reader, MeshData& meshData, std::vector<unsigned int>& vertexIndices, std::vector<glm::vec3>& tmp_vertices);
	// this function loads faces that only include vertices and textures!
	static void LoadFacesWithTextures(std::ifstream& obj, char* reader, MeshData& meshData, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& textureIndices, std::vector<glm::vec3>& tmp_vertices, std::vector<glm::vec2>& tmp_textures);

};

#endif // !OBJLOADER_H