#include "OBJloader.h"

MeshData OBJloader::LoadObject(const char * fileName, bool hasTextCoord)
{
	// initialize some usefull variables
	MeshData meshData;
	std::vector<glm::vec3> tmp_vertices;
	std::vector<glm::vec2> tmp_textures;
	std::ifstream obj(fileName);
	char reader[128];

	// check if the file exists
	if (!obj.is_open()) {
		std::cout << "Could not open/find: " << fileName << std::endl;
	}
	else {
		// read the first line to avoid conflicts
		obj.getline(reader, 128);
		// initialize the needed variables
		std::vector<unsigned int> vertexIndices, textureIndices, normalIndices;

		// load vertices
		OBJloader::LoadVertices(obj, reader, tmp_vertices);
		// load textures coord if enabled
		if (hasTextCoord) {
			OBJloader::LoadTextures(obj, reader, tmp_textures);
		}
		// load face with vertices, textures and normals
		if (hasTextCoord) {
			OBJloader::LoadFacesWithTextures(obj, reader, meshData, vertexIndices, textureIndices, tmp_vertices, tmp_textures);
		}
		// load face with vertices
		else {
			OBJloader::LoadFaces(obj, reader, meshData, vertexIndices, tmp_vertices);
		}
	}
	// return the meshData
	return meshData;
}

void OBJloader::LoadVertices(std::ifstream& obj, char* reader, std::vector<glm::vec3>& tmp_vertices)
{
	// eof stands for end_of_file
	while (!obj.eof()) {
		// v means we found a geometric vertices so we push it in the vector
		if (reader[0] == 'v' && reader[1] == ' ') {
			glm::vec3 tmpVertex;
			sscanf(reader, "v %f %f %f", &tmpVertex.x, &tmpVertex.y, &tmpVertex.z);
			tmp_vertices.push_back(tmpVertex);
			obj.getline(reader, 128);
			continue;
		}
		// vt means we found a textCoord so we break out of the loop
		if (reader[0] == 'v' && reader[1] == 't') {
			break;
		}
		// vn means we found a normCoord so we break out of the loop
		else if (reader[0] == 'v' && reader[1] == 'n') {
			break;
		}
		// f means we found a face so we break out of the loop
		else if (reader[0] == 'f') {
			break;
		}
		obj.getline(reader, 128);
	}
}

void OBJloader::LoadTextures(std::ifstream & obj, char * reader, std::vector<glm::vec2>& tmp_textures)
{
	// eof stands for end_of_file
	while (!obj.eof()) {
		// vt means we found a texture coordinate so we push it in the vector
		if (reader[0] == 'v' && reader[1] == 't') {
			glm::vec2 tmpTexture;
			sscanf(reader, "vt %f %f", &tmpTexture.x, &tmpTexture.y);
			tmp_textures.push_back(tmpTexture);
			obj.getline(reader, 128);
			continue;
		}
		// vn means we found a normCoord so we break out of the loop
		if (reader[0] == 'v' && reader[1] == 'n') {
			break;
		}
		// f means we found a face so we break out of the loop
		else if (reader[0] == 'f') {
			break;
		}
		obj.getline(reader, 128);
	}
}

void OBJloader::LoadFaces(std::ifstream& obj, char* reader, MeshData& meshData, std::vector<unsigned int>& vertexIndices, std::vector<glm::vec3>& tmp_vertices)
{
	while (!obj.eof()) {
		// if we found something else then a face we continue with the loop
		if (reader[0] != 'f') {
			obj.getline(reader, 256);
			continue;
		}
		// push the indices in to  a vector
		unsigned int a, b, c;
		sscanf(reader, "f %d %d %d", &a, &b, &c);

		vertexIndices.push_back(a - 1);
		vertexIndices.push_back(b - 1);
		vertexIndices.push_back(c - 1);

		obj.getline(reader, 256);
	}
	// the vertices for rendering
	meshData.amountVertices = vertexIndices.size() * 3;
	GLfloat* vertices;
	vertices = new GLfloat[meshData.amountVertices];
	// the vertices we will give to box2D
	int vertexIndicesSize = vertexIndices.size();
	b2Vec2* b2Vertices;
	b2Vertices = new b2Vec2[vertexIndicesSize];

	// place all of the vertices in the right place
	for (unsigned int i = 0; i < vertexIndicesSize; i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vertices[i * 3] = tmp_vertices[vertexIndex].x;
		vertices[i * 3 + 1] = tmp_vertices[vertexIndex].y;
		vertices[i * 3 + 2] = tmp_vertices[vertexIndex].z;

		b2Vertices[i].x = tmp_vertices[vertexIndex].x;
		b2Vertices[i].y = tmp_vertices[vertexIndex].y;
	}
	// setup meshData
	meshData.vertices = vertices;
	meshData.hasTextCoord = false;
	meshData.b2Vertices = b2Vertices;
}

void OBJloader::LoadFacesWithTextures(std::ifstream& obj, char* reader, MeshData& meshData, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& textureIndices, std::vector<glm::vec3>& tmp_vertices, std::vector<glm::vec2>& tmp_textures)
{
	while (!obj.eof()) {
		// if we found something else then a face we continue with the loop
		if (reader[0] != 'f') {
			obj.getline(reader, 256);
			continue;
		}
		// push the indices in to  a vector
		unsigned int a, b, c, d, e, f;
		sscanf(reader, "f %d/%d %d/%d %d/%d", &a, &b, &c, &d, &e, &f);
		
		vertexIndices.push_back(a - 1);
		textureIndices.push_back(b - 1);
		vertexIndices.push_back(c - 1);
		textureIndices.push_back(d - 1);
		vertexIndices.push_back(e - 1);
		textureIndices.push_back(f - 1);

		obj.getline(reader, 256);
	}
	// the vertices for rendering
	meshData.amountVertices = vertexIndices.size() * 5;
	GLfloat* vertices;
	vertices = new GLfloat[meshData.amountVertices];

	// the vertices we will give to box2D
	int vertexIndicesSize = vertexIndices.size();
	b2Vec2* b2Vertices;
	b2Vertices = new b2Vec2[vertexIndicesSize];

	// place all of the vertices in the right place
	for (unsigned int i = 0; i < vertexIndicesSize; i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vertices[i * 5] = tmp_vertices[vertexIndex].x;
		vertices[i * 5 + 1] = tmp_vertices[vertexIndex].y;
		vertices[i * 5 + 2] = tmp_vertices[vertexIndex].z;

		unsigned int textureIndex = textureIndices[i];
		vertices[i * 5 + 3] = tmp_textures[textureIndex].x;
		vertices[i * 5 + 4] = tmp_textures[textureIndex].y;

		b2Vertices[i].x = tmp_vertices[vertexIndex].x;
		b2Vertices[i].y = tmp_vertices[vertexIndex].y;
	}
	meshData.vertices = vertices;
	meshData.hasTextCoord = true;
	meshData.b2Vertices = b2Vertices;
}