#include "text.h"

Text::Text(std::string text, int size, const char* fontPath, glm::vec3 color, Shader* shader, Camera* camera, bool HUD) : Entity::Entity()
{
	this->text = text;
	this->shader = shader;
	this->camera = camera;
	this->color = color;
	this->HUD = HUD;
	// Initialize freetyp2
	// FreeType
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, fontPath, 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font: " << fontPath << " instead it loaded fonts/OpenSans-Regular.ttf" << std::endl;
		// Load a standard font from the fonts folder
		FT_New_Face(ft, "fonts/OpenSans-Regular.ttf", 0, &face);
	}

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, size);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load all of the 255 characters of ASCII set
	for (GLubyte c = 0; c < 255; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::~Text()
{
	//delete all of the graphics card memory associated with the texture. If you
	//don't call this method, the texture will stay in graphics card memory until you
	//close the application.
	for (GLubyte c = 0; c < 255; c++)
	{
		Character crh = characters[c];
		glDeleteTextures(1, &crh.TextureID);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Text::SetText(std::string text)
{
	this->text = text;
}

void Text::SetColor(glm::vec3 color)
{
	this->color = color;
}

void Text::Draw()
{
	GLfloat x = this->GetGlobalPosition().x;
	GLfloat y = this->GetGlobalPosition().y;
	// Use that Shader and set it's uniforms	
	shader->Use();
	shader->SetVec3Float("textColor", color);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = x + ch.Bearing.x * GetGlobalScale().x;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * GetGlobalScale().y;

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));
		model = glm::rotate(model, this->GetGlobalAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(this->GetGlobalScale().x, this->GetGlobalScale().y, 0.0f));
		shader->SetMatrix4("model", model);

		GLfloat w = ch.Size.x * GetGlobalScale().x;
		GLfloat h = ch.Size.y * GetGlobalScale().y;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			// Vertex positions		// uv positions
			{ 0.0f,     h,			0.0f, 0.0f },
			{ 0.0f,     0.0f,		0.0f, 1.0f },
			{ w,		0.0f,		1.0f, 1.0f },

			{ 0.0f,     h,			0.0f, 0.0f },
			{ w,		0.0f,       1.0f, 1.0f },
			{ w,		h,			1.0f, 0.0f }
		};
		// Render glyph texture over quad
		glActiveTexture(GL_TEXTURE0 + ch.TextureID);
		shader->SetInt("text", ch.TextureID);
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) /4 * 3, sizeof(vertices) / 4 * 2, vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * GetGlobalScale().x; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}
