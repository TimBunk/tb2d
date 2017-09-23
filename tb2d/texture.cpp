#include "texture.h"

int Tex::activeTex = 0;

Texture Tex::LoadTexture(const char * filePath, TextureWrap textureWrap, TextureFilter textureFilter, TextureType textureType)
{
	// Note to self the first texture of a ID is 1 instead of 0

	// define all needed variables
	GLuint id;
	std::string type;
	Texture texture;

	int width, height;
	unsigned char* data;

	// generate and bind the textures
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	// choose the entered wrapping
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
	// choose the entered filter
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

	// choose the entered type
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
	case normalMap:
		type = "normalMap";
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

	activeTex++;
	texture.id = id;
	texture.index = activeTex;
	texture.type = type;

	// return the texture
	return texture;
}

void Tex::SaveImage(const unsigned int * screenWidth, const unsigned int * screenHeight)
{
	int saveResult;
	saveResult = SOIL_save_screenshot("AwesomeScreenshot.png", SOIL_SAVE_TYPE_PNG, 0, 0, *screenWidth, *screenHeight);
	if (!saveResult) {
		std::cout << "Error in taking screenshot: " << SOIL_last_result() << std::endl;
	}
}
