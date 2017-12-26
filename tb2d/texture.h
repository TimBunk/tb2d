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
enum MipmapFilter {
	none, // Use no mipmap
	nearest_mipmap_nearest, // takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	nearest_mipmap_linear, // linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation. 
	linear_mipmap_nearest, // takes the nearest mipmap level and samples using linear interpolation. 
	linear_mipmap_linear // linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.
};

class Texture {
public:
	Texture(const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter);
	~Texture();

	unsigned int GetId();
private:
	unsigned int id;
};

#endif // !TEXTURE_H
