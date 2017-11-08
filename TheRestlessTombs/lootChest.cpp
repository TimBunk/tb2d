#include "lootChest.h"
#include "player.h"

LootChest::LootChest(int gold, Player* player, Shader* text, Camera* camera, Shader* shader, b2World* world) : Destructable::Destructable(camera, shader, world) {
	// initialize all of the variables with a value
	this->gold = gold;
	this->player = player;
	std::string s = std::to_string(gold);
	std::string ss = "+" + s;
	this->text = new Text("fonts/OpenSans-Regular.ttf", ss, 60, glm::vec4(1.0f, 0.88f, 0.42f, 1.0f), false, camera, text);
}

LootChest::~LootChest() {
	delete text;
}

void LootChest::Update(double deltaTime) {
	if (text->GetVisibility() > 0.0f && !alive) {
		// The alpha of the text goes minus the deltaTime so it takes 3 second for it to be invisible
		text->SetVisibility(text->GetVisibility() - deltaTime * 0.333f);
		// Move the text up 25 pixels in a second
		text->localPosition = glm::vec3(text->localPosition.x, text->localPosition.y - 50.0f * deltaTime, text->localPosition.z);
	}
}

void LootChest::Draw() {
	// Use the shader and draw the lootChest
	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(GetPositionInPixels(), this->GetGlobalPosition().z));
	model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
	shader->SetMatrix4("model", model);
	// Load the texture of the closed chest!
	if (alive) {
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}
	// Load the texture of the opened chest!
	else {
		glActiveTexture(GL_TEXTURE0 + chestOpened.id);
		shader->SetInt("ourTexture", chestOpened.id);
		glBindTexture(GL_TEXTURE_2D, chestOpened.id);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void LootChest::GiveTexture(Texture chestClosed, Texture chestOpened) {
	this->texture = chestClosed;
	this->chestOpened = chestOpened;
}

void LootChest::Destroy() {
	if (alive) {
		// Destroy only if alive and add the gold to the player and display the amount of gold you get on the screen
		alive = false;
		player->AddGold(gold);
		text->localPosition = glm::vec3(this->localPosition.x - (text->GetWidth() * 0.25f), this->localPosition.y, this->localPosition.z);
		this->AddChild(text);
	}
}

void LootChest::Reset() {
	// Reset the text
	text->localPosition = glm::vec3(text->localPosition.x, this->localPosition.y, text->localPosition.z);
	text->SetVisibility(1.0f);
	if (!alive) {
		this->RemoveChild(text);
		alive = true;
	}
}

void LootChest::SetActive(bool active) {
	if (body != NULL) {
		body->SetActive(active);
	}
}
