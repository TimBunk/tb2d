#include "text.h"

Text::Text(std::string text, Font font, glm::vec3 color, AlignmentX xAlignment, AlignmentY yAlignment) : Entity::Entity()
{
	// Get the default text renderer from the renderManager
	textRenderer = RenderManager::GetTextRenderer("freetype");
	// Intialize the variables
	this->font = font;
	this->color = color;
	this->xAlignment = xAlignment;
	this->yAlignment = yAlignment;
	// Set the text
	SetText(text);
}

Text::~Text()
{
	
}

void Text::Draw()
{
	// Send the information of this Text to the textRenderer
	textRenderer->Submit(this);
}

void Text::SetText(std::string text)
{
	this->text = text;
	width = 0;
	height = 0;
	vertices.clear();
	float posX = 0.0f;
	// Load all the glyps and get the correct vertices and textureCoordinates
	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		const char* cc = &c;
		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(font.font, cc);
		if (glyph != 0) {
			// Set the width and height
			width += glyph->advance_x;
			if (glyph->offset_y > height) {
				height = glyph->offset_y;
			}

			float x0 = posX + glyph->offset_x;
			float y0 = 0.0f - ((glyph->height - glyph->offset_y));
			float x1 = x0 + glyph->width;
			float y1 = y0 + glyph->height;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			vertices.push_back(glm::vec4(x0, y0, u0, v1));// lower left
			vertices.push_back(glm::vec4(x1, y0, u1, v1));// lower right
			vertices.push_back(glm::vec4(x0, y1, u0, v0)); // upper left
			vertices.push_back(glm::vec4(x1, y0, u1, v1));// lower right
			vertices.push_back(glm::vec4(x1, y1, u1, v0));// upper right
			vertices.push_back(glm::vec4(x0, y1, u0, v0)); // upper left

			posX += glyph->advance_x;
		}
	}
	// Set the alignment
	SetAlignment(xAlignment, yAlignment);
}

void Text::SetAlignment(AlignmentX xAlignment, AlignmentY yAlignment)
{
	this->xAlignment = xAlignment;
	this->yAlignment = yAlignment;
	// Calculate the offset for the alignment
	switch (xAlignment)
	{
	case leftX:
		offset.x = 0.0f;
		break;
	case centerX:
		offset.x = (width / 2.0f) * -1.0f;
		break;
	case rightX:
		offset.x = width * -1.0f;
		break;
	}

	switch (yAlignment)
	{
	case topY:
		offset.y = height * -1.0f;
		break;
	case centerY:
		offset.y = (height / 2.0f) * -1.0f;
		break;
	case bottomY:
		offset.y = 0.0f;
		break;
	}
}
