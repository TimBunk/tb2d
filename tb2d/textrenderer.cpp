#include "textrenderer.h"
#include "text.h"

TextRenderer::TextRenderer(Shader * shader, bool hud) : Renderer::Renderer(shader)
{
	this->hud = hud;

	// Generate and bind the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind the positions
	glGenBuffers(1, &VBO_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);

	// Generate and bind the positions
	glGenBuffers(1, &VBO_texture);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
	// Set attribute pointer for the position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);

	// Generate and bind the color
	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	// Set attribute pointer for the color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);

	// Gererate the model buffer
	glGenBuffers(1, &VBO_model);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_model);
	// set attribute pointers for matrix (4 times vec4)
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(3 * sizeof(glm::vec4)));

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	for (int i = 0; i < 32; i++) {
		activeTextureArray[i] = i;
	}
}

TextRenderer::~TextRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_position);
	glDeleteBuffers(1, &VBO_texture);
	glDeleteBuffers(1, &VBO_color);
	glDeleteBuffers(1, &VBO_model);
}

void TextRenderer::Submit(Text * text)
{
	int id = 0;
	bool found = false;
	for (; id < textureSlots.size(); id++) {
		if (text->GetAtlasID() == textureSlots[id]) {
			found = true;
			break;
		}
	}
	if (found == false) {
		if (textureSlots.size() == 32) {
			// TODO: Make a fix so that there can be more than 32 textures
			std::cout << "above 32 textures! " << std::endl;
		}
		textureSlots.push_back(text->GetAtlasID());
	}

	//glm::vec2 pos = text->GetGlobalPosition();
	float posX = 0.0f;
	for (int i = 0; i < text->GetText().length(); i++) {
		char c = text->GetText()[i];
		const char* cc = &c;
		ftgl::texture_glyph_t* glyph = texture_font_get_glyph(text->GetFont(), cc);
		if (glyph != 0) {
			float x0 = posX + glyph->offset_x;
			//std::cout << c << " offset = " << glyph->offset_y << " height = " << glyph->height << " difference = " << glyph->height - glyph->offset_y << std::endl;
			float y0 = 0.0f - ((glyph->height - glyph->offset_y));
			float x1 = x0 + glyph->width;
			float y1 = y0 + glyph->height;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			positions.push_back(glm::vec4(x0, y0, u0, v1));// lower left
			positions.push_back(glm::vec4(x1, y0, u1, v1));// lower right
			positions.push_back(glm::vec4(x0, y1, u0, v0)); // upper left
			positions.push_back(glm::vec4(x1, y0, u1, v1));// lower right
			positions.push_back(glm::vec4(x1, y1, u1, v0));// upper right
			positions.push_back(glm::vec4(x0, y1, u0, v0)); // upper left

			// Get the model matrix from the text
			glm::mat4 model = text->GetModelMatrix();
			model = glm::translate(model, glm::vec3(text->GetOffset().x, text->GetOffset().y, 0.0f));
			//model = glm::scale(model, glm::vec3(1080.0f, 1080.0f, 0.0f));
			// Push back 6 times because we have 6 vertices
			for (int i = 0; i < 6; i++) {
				textures.push_back((GLfloat(id) + 1.0f));
				colors.push_back(text->GetColor());
				matrices.push_back(model);
			}
			posX += glyph->advance_x;
		}
	}
}

void TextRenderer::Render(Camera * camera)
{
	// If there is nothing to draw
	if (positions.size() == 0) { return; };

	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	if (!hud) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	else {
		shader->SetMatrix4("view", glm::mat4());
	}

	shader->SetIntArray("textures", activeTextureArray, 32);

	// Bind the VAO
	glBindVertexArray(VAO);

	for (int i = 0; i < textureSlots.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
	}

	// Fill all of the buffers with their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_position);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec4), &positions[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
	glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(GLfloat), &textures[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_model);
	glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), &matrices[0], GL_STREAM_DRAW);

	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// bind texture and draw elements
	glDrawArrays(GL_TRIANGLES, 0, positions.size());

	// Unbind the VAO and texture
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Clear all of the data
	positions.clear();
	textures.clear();
	colors.clear();
	matrices.clear();

	textureSlots.clear();
}
