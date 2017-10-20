#include "text.h"

Text::Text(const char* filePath, std::string text, int fontSize, glm::vec4 color, bool HUD, Camera* camera, Shader* shader) : Entity::Entity() {
	// Set the values of the needed variables
	this->filePath = filePath;
	this->currentText = text;
	this->fontSize = fontSize;
	this->color = color;
	this->HUD = HUD;
	this->camera = camera;
	this->shader = shader;
	width = 0;
	height = 0;
	visibility = 1.0f;

	//Initialize SDL_ttf
	if( TTF_Init() == -1 ) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	// generate the needed texture for the text
	glGenTextures(1, &textureId);
	//Create the texture
	fontColor = {color.x * 255.0f, color.y * 255.0f, color.z * 255.0f, color.w * 255.0f};
	CreateText();
}

Text::~Text() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Text::SetText(std::string text) {
	if (text != currentText) {
		currentText = text;
		CreateText();
	}
}

void Text::SetFontSize(int fontSize) {
	if (this->fontSize != fontSize) {
		this->fontSize = fontSize;
		CreateText();
	}
}

void Text::SetColor(glm::vec4 color) {
	if (this->color != color) {
		this->color = color;
		fontColor = {color.x * 255.0f, color.y * 255.0f, color.z * 255.0f, color.w * 255.0f};
		CreateText();
	}
}

void Text::SetVisibility(float value) {
	this->visibility = value;
}

void Text::Draw() {
	shader->Use();
	shader->SetFloat("visibility", visibility);
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	glm::mat4 model;
	model = glm::translate(model, this->localPosition);
	shader->SetMatrix4("model", model);
	if (!HUD) {
		shader->SetMatrix4("view", camera->GetViewMatrix());
	}
	// Apply the texture to the shader
	glActiveTexture(GL_TEXTURE0 + textureId);
	shader->SetInt("ourTexture", textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

std::string Text::GetText() {
	return currentText;
}

unsigned int Text::GetFontSize() {
	return fontSize;
}

glm::vec4 Text::GetColor() {
	return color;
}

float Text::GetVisibility() {
	return visibility;
}

int Text::GetWidth() {
	return width;
}

int Text::GetHeight() {
	return height;
}

void Text::CreateText() {
	// Open the font
	font = TTF_OpenFont(filePath, fontSize);
	// Create a SDL_surface
	//SDL_Surface* sdlSurface = TTF_RenderText_Blended(font, currentText.c_str(), fontColor);
	SDL_Surface* sdlSurface = TTF_RenderText_Blended_Wrapped(font, currentText.c_str(), fontColor,  4096);
	// Create texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->width = sdlSurface->w;
	this->height = sdlSurface->h;
	// Set the vertices/indices of the texture
	float vertices[] = {
		// vertPosition					uvPosition
		0.0f, -0.5f * sdlSurface->h,	0.0f, 0.0f,//bottomLeft
		0.5f * sdlSurface->w, -0.5f * sdlSurface->h,	1.0f, 0.0f,//bottomRight
		0.5 * sdlSurface->w, 0.5f *sdlSurface->h,	1.0f, 1.0f,// topRight
		0.0f, 0.5f * sdlSurface->h, 	0.0f, 1.0f// topLeft
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	if (VAO != 0) {
		// Delete the old VAO
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	// Create the VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set the vertices
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	SDL_FreeSurface(sdlSurface);
	// Close the font
	TTF_CloseFont(font);
}
