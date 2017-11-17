#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <map>

#include "shader.h"
#include "entity.h"

#include <ft2build.h>
#include FT_FREETYPE_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text : public Entity {
public:
	Text(std::string text, Shader* shader, const char* fontPath, glm::vec3 color);
	~Text();

	void SetText(std::string text);
	void SetColor(glm::vec3 color);
	void Draw(glm::mat4 projection);
private:
	Shader* shader;
	std::map<GLchar, Character> characters;
	GLuint VAO, VBO;

	std::string text;
	glm::vec3 color;
};

#endif //! TEXT_H