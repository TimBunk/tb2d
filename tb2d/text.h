/**
* @file text.h
*
* @brief The Text header file.
*/

#ifndef TEXT_H
#define TEXT_H

#include "entity.h"
#include "renderManager.h"

/**
* @brief The Text class
*/
class Text : public Entity
{
public:
	/// @brief AlignmentX is the alignment of the text on the x-axis
	enum AlignmentX {
		leftX,
		centerX,
		rightX
	};
	/// @brief AlignmentY is the alignment of the text on the y-axis
	enum AlignmentY {
		topY,
		centerY,
		bottomY
	};
	/// @brief Constructor of the Text
	/// @param text is the text you want to be renderd
	/// @param Font is the font you want to use, this font can be received from the ResourceManager
	/// @param color is the color of the text
	/// @param xAlignment the alignment of the text on the x-axis
	/// @param yAlignment the alignment of the text on the y-axis
	Text(std::string text, Font font, glm::vec3 color, AlignmentX xAlignment, AlignmentY yAlignment);
	/// @brief Destructor of the Text
	~Text();

	/// @brief Draw submits this Text to the TextRenderer
	/// @return void
	void Draw();

	/// @brief SetText sets the string you want to render
	/// @param text is the string you want to render
	/// @return void
	void SetText(std::string text);
	/// @brief SetTextRenderer sets the TextRenderer for this Text. TextRenderer can be received from the RenderManager
	/// @param textRenderer is the new TextRenderer for this Text
	/// @return void
	void SetTextRenderer(TextRenderer* textRenderer) { this->textRenderer = textRenderer; }
	/// @brief SetAlignment sets the alignment of this Text
	/// @param xAlignment is the alignment on the x-axis
	/// @param yAlignment is the alignment on the y-axis
	/// @return void
	void SetAlignment(AlignmentX xAlignment, AlignmentY yAlignment);
	/// @brief SetFont sets the font for this Text.
	/// @param font is the Font you want to use for this Text. Font's can be receieved from the ResourceManager
	/// @return void
	void SetFont(Font font) { this->font = font; }
	/// @brief SetColor sets the color for this Text
	/// @param color the color you want to use for this Text
	/// @return void
	void SetColor(glm::vec4 color) { this->color = color; }

	/// @brief GetText returns the string of this Text
	/// @return string
	std::string GetText() { return text; }
	/// @brief GetAlasID return the atlasTextureID of the Font
	/// @return unsigned int
	unsigned int GetAtlasID() { return font.textureAtlas->id; }
	/// @brief GetFont return the font of the Font
	/// @return ftgl::texture_font_t*
	ftgl::texture_font_t* GetFont() { return font.font; }
	/// @brief GetColor returns the color that is being used by this Text
	/// @return glm::vec3
	glm::vec3 GetColor() { return color; }
	/// @brief GetWidth returns the width of this Text
	/// @return float
	float GetWidth() { return width; }
	/// @brief GetHeight returns the height of this Text
	/// @return float
	float GetHeight() { return height; }
	/// @brief returns the offset of the Text that starts from the bottom left
	/// @return glm::vec2
	glm::vec2 GetOffset() { return offset; }

	/// @brief GetVertices returns a list of vertices that contains position and uv coordinates for the text
	/// @return vector<glm::vec4>
	std::vector<glm::vec4> GetVertices() { return vertices; }

private:
	TextRenderer* textRenderer; ///< @brief textRenderer is the TextRenderer that is being used by this Text
	std::vector<glm::vec4> vertices; ///< @brief vertices is a vector that contains all of the position + uv coordinates(x,y position - y, w uv's)

	std::string text; ///< @brief text is the string that has to be rendered
	Font font; ///< @brief font is the Font that is being used for rendering this Text
	glm::vec3 color; ///< @brief color the color of this Text

	float width; ///< @brief width is the width
	float height; ///< @brief height is the height
	
	glm::vec2 offset; ///< @brief offset is the offset from the bottom left
	AlignmentX xAlignment; ///< @brief xAlignment is the alignment on the x-axis
	AlignmentY yAlignment; ///< @brief yAlignment is the alignment on the y-axis
};

#endif // !TEXT_H