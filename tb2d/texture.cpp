#include "texture.h"

Texture::Texture(const char * filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType)
{
	int width, height;
	// unsigned char, which gives you at least the 0 to 255 range.
	unsigned char* data;

	// generate and bind the textures
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// get the entered wrapping
	switch (textureWrap) {
	case repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case mirrored_repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case clamp_to_edge:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case clamp_to_border:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	}
	// get the entered filter
	switch (textureFilter) {
	case linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	// get the entered type
	switch (textureType) {
	case diffuse:
		type = "diffuse";
		break;
	case specular:
		type = "specular";
		break;
	case emission:
		type = "emission";
		break;
	}
	// load the image data and create Mipmap
	data = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGBA);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load '" << filePath << "' : " << SOIL_last_result() << std::endl;
	}

	// free the allocated memory
	SOIL_free_image_data(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

unsigned int Texture::GetId()
{
	return id;
}

std::string Texture::GetType()
{
	return type;
}
