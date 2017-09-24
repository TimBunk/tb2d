#include "text.h"

Text::Text(const char* filePath, const char* text, int fontSize, glm::vec4 color, bool HUD, float width, float height, glm::mat4 projection) {
	// Set the values of the needed variables
	this->filePath = filePath;
	this->currentText = text;
	this->fontSize = fontSize;
	this->HUD = HUD;
	// Set the hud shader, NOTE that the HUD shader doesn't move
	if (HUD) {
		shader = new Shader("shaders//textHUD.vs", "shaders//textHUD.fs");
	}
	// Set the default shader, NOTE that the default shader moves accordingly to the camera
	else {
		shader = new Shader("shaders//text.vs", "shaders//text.fs");
	}
	// Set the uniforms for the shader;
	shader->Use();
	shader->SetMatrix4("projection", projection);
	model = glm::translate(model, glm::vec3(0.0f));
	shader->SetMatrix4("model", model);
	// Set the vertices/indices of the texture
	float vertices[] = {
		// vertPosition					uvPosition
		-0.5f * width, -0.5f * height,	0.0f, 0.0f,//bottomLeft
		0.5f * width, -0.5f * height,	1.0f, 0.0f,//bottomRight
		0.5f * width, 0.5f * height,	1.0f, 1.0f,// topRight
		-0.5f * width, 0.5f * height, 	0.0f, 1.0f// topLeft
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
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

	//Initialize SDL_ttf
	if( TTF_Init() == -1 ) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	// generate the needed texture for the text
	glGenTextures(1, &textureId);
	//Create the texture
	fontColor = {color.x * 255, color.y * 255, color.z * 255, color.w * 255};
	CreateText();
}

Text::~Text() {
	delete shader;
}

void Text::SetText(const char* text) {
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
		fontColor = {color.x * 255, color.y * 255, color.z * 255, color.w * 255};
		CreateText();
	}
}

void Text::SetPosition(glm::vec3 position) {
	model = glm::translate(model, position);
	shader->SetMatrix4("model", model);
}

void Text::Draw(glm::mat4 view) {
	shader->Use();
	shader->SetMatrix4("view", view);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Text::DrawHUD() {
	shader->Use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Text::CreateText() {
	// Open the font
	font = TTF_OpenFont(filePath, fontSize);
	// Create a SDL_surface
	SDL_Surface* sdlSurface = TTF_RenderText_Blended(font, currentText, fontColor);
	// Create texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(sdlSurface);
	// Apply the texture to the shader
	shader->Use();
	glActiveTexture(GL_TEXTURE0 + textureId);
	shader->SetInt("ourTexture", textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glActiveTexture(GL_TEXTURE0);
	// Close the font
	TTF_CloseFont(font);
}
