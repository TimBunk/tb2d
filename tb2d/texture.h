/**
* @file texture.h
*
* @brief The Texture header file.
*/


#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL2.h>

/// @brief TextureWrap is the wrapping for the texture
enum TextureWrap {
	repeat,
	mirrored_repeat,
	clamp_to_edge,
	clamp_to_border
};
/// @brief TextureFilter is the filter for the texture
enum TextureFilter {
	linear,
	nearest
};
/// @brief MipmapFilter is the filter for the texture
enum MipmapFilter {
	none, // Use no mipmap
	nearest_mipmap_nearest, // takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
	nearest_mipmap_linear, // linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation. 
	linear_mipmap_nearest, // takes the nearest mipmap level and samples using linear interpolation. 
	linear_mipmap_linear // linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.
};

/**
* @brief The Texture class
*/
class Texture {
public:
	/// @brief Constructor of the Texture
	/// @param filePath is the filePath to a texture for example: "textures/example.jpg"
	/// @param textureWrap is the wrapping for the texture
	/// @param textureFilter is the filter for the texture
	/// @param mimmapFilter is the filter for the mimpmap of the texture
	Texture(const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter);
	/// @brief Destructor of the Texture
	~Texture();

	/// @brief GetID returns the id of the texture
	unsigned int GetId() { return id; }
private:
	unsigned int id; ///< @brief id is the id of the texture
};

#endif // !TEXTURE_H
