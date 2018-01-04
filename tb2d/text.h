#ifndef TEXT_H
#define TEXT_H

#include "entity.h"
#include "camera.h"
#include "resourceManager.h"
#include "renderManager.h"

class Text : public Entity
{
public:
	enum AlignmentX {
		leftX,
		centerX,
		rightX
	};

	enum AlignmentY {
		topY,
		centerY,
		bottomY
	};

	Text(std::string text, Font font, glm::vec3 color, AlignmentX xAlignment, AlignmentY yAlignment);
	~Text();

	void Draw();

	void SetText(std::string text);
	void SetTextRenderer(TextRenderer* textRenderer) { this->textRenderer = textRenderer; }
	void SetAlignment(AlignmentX xAlignment, AlignmentY yAlignment);
	void SetFont(Font font) { this->font = font; }

	std::string GetText() { return text; }
	unsigned int GetAtlasID() { return font.textureAtlas->id; }
	ftgl::texture_font_t* GetFont() { return font.font; }
	glm::vec3 GetColor() { return color; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	glm::vec2 GetOffset() { return offset; }

private:
	TextRenderer* textRenderer;

	std::string text;
	Font font;
	glm::vec3 color;

	float width;
	float height;

	glm::vec2 offset;
	AlignmentX xAlignment;
	AlignmentY yAlignment;
};

#endif // !TEXT_H