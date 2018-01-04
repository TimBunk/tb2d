#include "text.h"

Text::Text(std::string text, Font font, glm::vec3 color, AlignmentX xAlignment, AlignmentY yAlignment) : Entity::Entity()
{
	textRenderer = RenderManager::GetTextRendererer("freetype");
	this->font = font;
	this->color = color;
	this->xAlignment = xAlignment;
	this->yAlignment = yAlignment;

	SetText(text);
}

Text::~Text()
{
	
}

void Text::Draw()
{
	textRenderer->Submit(this);
}

void Text::SetText(std::string text)
{
	this->text = text;
	width = 0;
	height = 0;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		const char* cc = &c;
		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(font.font, cc);
		if (glyph != 0) {
			width += glyph->advance_x;
			if (glyph->offset_y > height) {
				height = glyph->offset_y;
			}
		}
	}
	SetAlignment(xAlignment, yAlignment);
}

void Text::SetAlignment(AlignmentX xAlignment, AlignmentY yAlignment)
{
	this->xAlignment = xAlignment;
	this->yAlignment = yAlignment;

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
