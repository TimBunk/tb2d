#include "shop.h"
#include "player.h"

Shop::Shop(Player* player, ResourceManager* rm, Input* input, Camera* camera, Shader* shader, b2World* world) : B2Entity::B2Entity(camera, shader, world) {
	active = false;
	this->player = player;
	shopWrapper = new Scene(camera);
	textShop = new Text("fonts/OpenSans-Regular.ttf", "SHOP", 90, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	textShop->localPosition = glm::vec3(camera->screenWidth/2 - textShop->GetWidth()/4, 50.0f, 1.0f);
	shopWrapper->AddChild(textShop);
	textPlayerUpgrades = new Text("fonts/OpenSans-Regular.ttf", "UPGRADES", 70, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	textPlayerUpgrades->localPosition = glm::vec3(camera->screenWidth/4 - textPlayerUpgrades->GetWidth()/4, 100.0f, 1.0f);
	shopWrapper->AddChild(textPlayerUpgrades);
	textItems = new Text("fonts/OpenSans-Regular.ttf", "SHOP", 90, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));

	healthUpgrade = new Button(camera->screenWidth/4, 200, 280, 50, true, "health upgrade", glm::vec4(1.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	healthUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(healthUpgrade);
	speedUpgrade = new Button(camera->screenWidth/4, 275, 280, 50, true, "speed upgrade", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	speedUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(speedUpgrade);
	damageUpgrade = new Button(camera->screenWidth/4, 350, 280, 50, true, "damage upgrade", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	damageUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(damageUpgrade);
	buttonContinue = new Button(camera->screenWidth/2, 500, 200, 60, true, "continue", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	shopWrapper->AddChild(buttonContinue);

	// health
	health = 4;
	costHealthUpgrade = 550;
	currentHealthUpgrade = 0;
	maxHealthUpgrades = 2;
	healthUpgrade->SetText(CreateUpgradeText("Extra live", currentHealthUpgrade, maxHealthUpgrades, costHealthUpgrade));
	// speed
	speed = 6.0f;
	costSpeedUpgrade = 400;
	currentSpeedUpgrade = 0;
	maxSpeedUpgrades = 2;
	speedUpgrade->SetText(CreateUpgradeText("Increase speed by 1", currentSpeedUpgrade, maxSpeedUpgrades, costSpeedUpgrade));
	// damage
	damage = 1;
	costDamageUpgrade = 950;
	currentDamageUpgrade = 0;
	maxDamageUpgrades = 2;
	damageUpgrade->SetText(CreateUpgradeText("Increase damage by 1", currentDamageUpgrade, maxDamageUpgrades, costDamageUpgrade));
}

Shop::~Shop() {
	delete textShop;
	delete textPlayerUpgrades;
	delete textItems;
	delete healthUpgrade;
	delete speedUpgrade;
	delete damageUpgrade;
	delete buttonContinue;
}

void Shop::Update(float deltaTime) {
	if (active) {
		shopWrapper->UpdateChilderen(shopWrapper, deltaTime);
		// HealthUpgrade
		if (healthUpgrade->Hover() && player->GetGold() >= costHealthUpgrade && currentHealthUpgrade < maxHealthUpgrades) {
			healthUpgrade->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
			if (healthUpgrade->Down()) {
				player->AddGold(costHealthUpgrade * -1);
				currentHealthUpgrade++;
				healthUpgrade->SetText(CreateUpgradeText("Extra live", currentHealthUpgrade, maxHealthUpgrades, costHealthUpgrade));
				health++;
				player->UpgradeHealth(health);
			}
		}
		else if (player->GetGold() >= costHealthUpgrade && currentHealthUpgrade < maxHealthUpgrades) {
			healthUpgrade->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
		}
		else {
			healthUpgrade->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
		}
		// SpeedUpgrade
		if (speedUpgrade->Hover() && player->GetGold() >= costSpeedUpgrade && currentSpeedUpgrade < maxSpeedUpgrades) {
			speedUpgrade->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
			if (speedUpgrade->Down()) {
				player->AddGold(costSpeedUpgrade * -1);
				currentSpeedUpgrade++;
				speedUpgrade->SetText(CreateUpgradeText("Increase speed by 1", currentSpeedUpgrade, maxSpeedUpgrades, costSpeedUpgrade));
				speed++;
				player->UpgradeSpeed(speed);
			}
		}
		else if (player->GetGold() >= costSpeedUpgrade && currentSpeedUpgrade < maxSpeedUpgrades) {
			speedUpgrade->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
		}
		else {
			speedUpgrade->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
		}
		// DamageUpgrade
		if (damageUpgrade->Hover() && player->GetGold() >= costDamageUpgrade && currentDamageUpgrade < maxDamageUpgrades) {
			damageUpgrade->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
			if (damageUpgrade->Down()) {
				player->AddGold(costDamageUpgrade * -1);
				currentDamageUpgrade++;
				damageUpgrade->SetText(CreateUpgradeText("Increase damage by 1", currentDamageUpgrade, maxDamageUpgrades, costDamageUpgrade));
				damage++;
				player->UpgradeDamage(damage);
			}
		}
		else if (player->GetGold() >= costDamageUpgrade && currentDamageUpgrade < maxDamageUpgrades) {
			damageUpgrade->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
		}
		else {
			damageUpgrade->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
		}
		if (buttonContinue->Hover()) {
			buttonContinue->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
			if (buttonContinue->Down()) {
				_SetActive(false);
			}
		}
		else {
			buttonContinue->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
		}
	}
}

void Shop::Draw() {
	if (!active) {
		shader->Use();
		shader->SetMatrix4("projection", camera->GetProjectionMatrix());
		shader->SetMatrix4("view", camera->GetViewMatrix());
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(GetPositionInPixels(), this->GetGlobalPosition().z));
		model = glm::rotate(model, GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(Window::m2p, Window::m2p, 0.0f));
		shader->SetMatrix4("model", model);
		glActiveTexture(GL_TEXTURE0 + texture.id);
		shader->SetInt("ourTexture", texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(0);
	}
}

void Shop::_SetActive(bool active) {
	this->active = active;
}

bool Shop::IsActive() {
	return active;
}

std::string Shop::CreateUpgradeText(std::string text, int currentUpgrade, int maxUpgrade, int cost) {
	std::string current = std::to_string(currentUpgrade);
	std::string max = std::to_string(maxUpgrade);
	std::string _cost = std::to_string(cost);
	std::string result = text;
	result +=  " ";
	result +=  current;
	result += "/";
	result += max;
	result += " $";
	result += _cost;
	return result;
}
