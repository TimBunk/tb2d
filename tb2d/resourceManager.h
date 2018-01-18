/**
* @file resourceManager.h
*
* @brief The ResourceManager header file.
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "texture.h"
#include "shader.h"

#include <GL/glew.h>
#include <freetype-gl\freetype-gl.h>

/// @brief Font contains the font and the textureAtlas that contains all of the characters
struct Font {
	ftgl::texture_atlas_t* textureAtlas = nullptr; ///< @brief textureAtlas is a atlas that contains every characters of the font
	ftgl::texture_font_t* font = nullptr; ///< @brief font is the actual font that contains all of the glyphs
};

/**
* @brief The ResourceManager class
*/
class ResourceManager {
public:
	/// @brief Initialize creates a instance of the resourceManager as a singleton
	/// @return void
	static void Initialize();
	/// @brief Destroy calls the deconstructor of the resourceManager
	/// @return void
	static void Destroy();

	/// @brief CreateShader creates a shader and saves it in a map
	/// @param nameOfShader is the name for the shader so that you can always get back the shader by its name when you created it
	/// @param vertexPath is the path to the vertex shader for example: "shaders//shader.vs"
	/// @param fragmentPath is the path tot the fragment shader for example: "shaders//shader.fs"
	/// @return void
	static void CreateShader(std::string nameOfShader, const char* vertexPath, const char* fragmentPath);
	/// @brief GetShader return a shader. NOTE that that shader needed to be created first by calling CreateShader
	/// @param name is the name of the created shader you would like to receive
	/// @return Shader*
	static Shader* GetShader(std::string name);

	/// @brief CreateTexture creates a texture and saves it in a map
	/// @param nameOfTexture is the name foor the texture so that you can always get back the texture by its name when you created it
	/// @param filePath the filePath to a texture for example: "textures/example.jpg"
	/// @param textureWrap is the wrapping you would like to use for that texture for example: TextureWrap::repeat
	/// @param textureFilter is the filter you would like to use for that texture for example: TextureFilter::linear
	/// @param mimmapFilter is the filter you would like to use for mipmapping for example: MipmapFilter::linear_mipmap_linear
	/// @return void
	static void CreateTexture(std::string nameOfTexture, const char* filePath, TextureWrap textureWrap, TextureFilter textureFilter, MipmapFilter mipmapFilter);
	/// @brief GetTexture returns a texture. NOTE that that texture needed to be created first by calling CreateTexture
	/// @param name is the name of the created texture you would like to receive
	static Texture* GetTexture(std::string name);

	/// @brief GetFont will search through a map of fonts and return the correct one. If no font was found in the map a new one will be created with the specified info received from the parameters
	/// @param filePath is the filepath to the font for example: "fonts/arial.ttf"
	/// @param textureAtlasSize will be the texture size of the atlas squared
	/// @param fontSize is the font size in pixels
	static Font GetFont(std::string filePath, int textureAtlasSize, int fontSize);

private:
	/// @brief Constructor of the ResourceManager
	ResourceManager();
	/// @brief Destructor of the ResourceManager
	~ResourceManager();

	static ResourceManager* rm; ///< @brief rm is the singleton instance of the resourceManager
	std::map<std::string, Shader*> shaders; ///< @brief shaders is a map of shaders
	std::map<std::string, Texture*> textures; ///< @brief textures is a map of textures
	std::map<std::string, std::map<int, std::map<int, Font>>> fonts; ///< @brief fonts is a nested map with all of the data to save a font
};

#endif // !RESOURCEMANGER_H
