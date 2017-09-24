#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include "SOIL2/SOIL2.h"

struct Texture {
	unsigned int id;
	std::string type;
};

enum TextureWrap {
	repeat,
	mirrored_repeat,
	clamp_to_edge,
	clamp_to_border
};
enum TextureFilter {
	linear,
	nearest
};
enum TextureType {
	diffuse,
	specular,
	emission,
	normalMap
};

class Tex {

public:

	static Texture LoadTexture(const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType);
	static void SaveImage(const unsigned int* screenWidth, const unsigned int* screenHeight);
};

#endif // !TEXTURE_H
