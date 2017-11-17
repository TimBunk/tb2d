#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL2.h>

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
	emission
};

class Texture {
public:
	Texture(const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType);
	~Texture();

	unsigned int GetId();
	std::string GetType();
private:
	unsigned int id;
	std::string type;
};

#endif // !TEXTURE_H
