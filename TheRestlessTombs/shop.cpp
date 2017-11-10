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
	textItems = new Text("fonts/OpenSans-Regular.ttf", "ITEMS", 70, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	textItems->localPosition = glm::vec3(camera->screenWidth/4*3 - textItems->GetWidth()/4, 100.0f, 1.0f);
	shopWrapper->AddChild(textItems);
	std::string playerGoldString = "Gold: ";
	playerGoldString += std::to_string(player->GetGold());
	playerGold = new Text("fonts/OpenSans-Regular.ttf", playerGoldString, 60, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	playerGold->localPosition = glm::vec3(50.0f, 450.0f, 1.0f);
	shopWrapper->AddChild(playerGold);
	playerInventory = new Text("fonts/OpenSans-Regular.ttf", "Inventory: empty", 60, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true, camera, rm->GetShader("textHud"));
	playerInventory->localPosition = glm::vec3(50.0f, 525.0f, 1.0f);
	shopWrapper->AddChild(playerInventory);

	// upgrades
	healthUpgrade = new Button(camera->screenWidth/4, 200, 290, 50, true, "health upgrade", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	healthUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(healthUpgrade);
	speedUpgrade = new Button(camera->screenWidth/4, 275, 290, 50, true, "speed upgrade", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	speedUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(speedUpgrade);
	damageUpgrade = new Button(camera->screenWidth/4, 350, 290, 50, true, "damage upgrade", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	damageUpgrade->SetTextFontSize(40);
	shopWrapper->AddChild(damageUpgrade);
	// continue
	buttonContinue = new Button(camera->screenWidth/2, 500, 200, 60, true, "continue", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	shopWrapper->AddChild(buttonContinue);
	// items
	buttonHealthPotion = new Button(camera->screenWidth/4 * 3, 200, 290, 50, true, "health potion", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	buttonHealthPotion->SetTextFontSize(40);
	shopWrapper->AddChild(buttonHealthPotion);
	buttonSpeedPotion = new Button(camera->screenWidth/4 * 3, 275, 290, 50, true, "speed potion", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	buttonSpeedPotion->SetTextFontSize(40);
	shopWrapper->AddChild(buttonSpeedPotion);
	buttonDamagePotion = new Button(camera->screenWidth/4 * 3, 350, 290, 50, true, "damage potion", glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f), input, camera, rm);
	buttonDamagePotion->SetTextFontSize(40);
	shopWrapper->AddChild(buttonDamagePotion);

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
	// healthPotion
	healthPotion = new HealthPotion(1, camera, rm->GetShader("shader"), world);
	healthPotion->GiveTexture(rm->GetTexture("healthPotion"));
	healthPotionTexture = new Hud(camera->screenWidth/4*3 + 115, 200, 30, 36, camera, rm->GetShader("hud"), rm->GetTexture("healthPotion"));
	shopWrapper->AddChild(healthPotionTexture);
	costHealthPotion = 250;
	buttonHealthPotion->SetText("Health potion $250");
	// speedPotion
	speedPotion = new SpeedPotion(2.0f, -0.15f, 4.0f, camera, rm->GetShader("shader"), world);
	speedPotion->GiveTexture(rm->GetTexture("speedPotion"));
	speedPotionTexture = new Hud(camera->screenWidth/4*3 + 115, 275, 30, 36, camera, rm->GetShader("hud"), rm->GetTexture("speedPotion"));
	shopWrapper->AddChild(speedPotionTexture);
	costSpeedPotion = 250;
	buttonSpeedPotion->SetText("Speed potion $250");
	// damagePotion
	damagePotion = new DamagePotion(1.0f, 5.0f, camera, rm->GetShader("shader"), world);
	damagePotion->GiveTexture(rm->GetTexture("damagePotion"));
	damagePotionTexture = new Hud(camera->screenWidth/4*3 + 115, 350, 30, 36, camera, rm->GetShader("hud"), rm->GetTexture("damagePotion"));
	shopWrapper->AddChild(damagePotionTexture);
	costDamagePotion = 250;
	buttonDamagePotion->SetText("Damage potion $250");
}

Shop::~Shop() {
	delete textShop;
	delete textPlayerUpgrades;
	delete textItems;
	delete playerGold;
	delete playerInventory;
	delete healthUpgrade;
	delete speedUpgrade;
	delete damageUpgrade;
	delete buttonContinue;
	delete buttonHealthPotion;
	delete healthPotion;
	delete healthPotionTexture;
	delete buttonSpeedPotion;
	delete speedPotion;
	delete speedPotionTexture;
	delete buttonDamagePotion;
	delete damagePotion;
	delete damagePotionTexture;
}

void Shop::Update(double deltaTime) {
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
				std::string playerGoldString = "Gold: ";
				playerGoldString += std::to_string(player->GetGold());
				playerGold->SetText(playerGoldString);
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
				std::string playerGoldString = "Gold: ";
				playerGoldString += std::to_string(player->GetGold());
				playerGold->SetText(playerGoldString);
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
				std::string playerGoldString = "Gold: ";
				playerGoldString += std::to_string(player->GetGold());
				playerGold->SetText(playerGoldString);
			}
		}
		else if (player->GetGold() >= costDamageUpgrade && currentDamageUpgrade < maxDamageUpgrades) {
			damageUpgrade->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
		}
		else {
			damageUpgrade->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
		}
		// Continue button
		if (buttonContinue->Hover()) {
			buttonContinue->SetColor(glm::vec4(0.40f, 0.35f, 0.47f, 1.0f));
			if (buttonContinue->Down()) {
				_SetActive(false);
			}
		}
		else {
			buttonContinue->SetColor(glm::vec4(0.505882353f, 0.411764706f, 0.458823529f, 1.0f));
		}

		// Update playerInventory
		if (!player->IsInventoryFull()) {
			playerInventory->SetText("Inventory: empty");

			// HealthPotion
			if (buttonHealthPotion->Hover() && player->GetGold() >= costHealthPotion) {
				buttonHealthPotion->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
				if (buttonHealthPotion->Down()) {
					player->AddGold(costHealthPotion * -1);
					player->GiveItem(healthPotion);
					std::string playerGoldString = "Gold: ";
					playerGoldString += std::to_string(player->GetGold());
					playerGold->SetText(playerGoldString);
				}
			}
			else if (player->GetGold() >= costHealthPotion) {
				buttonHealthPotion->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
			}
			else {
				buttonHealthPotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
			}
			// SpeedPotion
			if (buttonSpeedPotion->Hover() && player->GetGold() >= costSpeedPotion) {
				buttonSpeedPotion->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
				if (buttonSpeedPotion->Down()) {
					player->AddGold(costSpeedPotion * -1);
					player->GiveItem(speedPotion);
					std::string playerGoldString = "Gold: ";
					playerGoldString += std::to_string(player->GetGold());
					playerGold->SetText(playerGoldString);
				}
			}
			else if (player->GetGold() >= costSpeedPotion) {
				buttonSpeedPotion->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
			}
			else {
				buttonSpeedPotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
			}
			// DamagePotion
			if (buttonDamagePotion->Hover() && player->GetGold() >= costDamagePotion) {
				buttonDamagePotion->SetColor(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
				if (buttonDamagePotion->Down()) {
					player->AddGold(costDamagePotion * -1);
					player->GiveItem(damagePotion);
					std::string playerGoldString = "Gold: ";
					playerGoldString += std::to_string(player->GetGold());
					playerGold->SetText(playerGoldString);
				}
			}
			else if (player->GetGold() >= costDamagePotion) {
				buttonDamagePotion->SetColor(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
			}
			else {
				buttonDamagePotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
			}
		}
		else {
			playerInventory->SetText("Inventory: full");
			buttonHealthPotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
			buttonSpeedPotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
			buttonDamagePotion->SetColor(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
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
	std::string playerGoldString = "Gold: ";
	playerGoldString += std::to_string(player->GetGold());
	playerGold->SetText(playerGoldString);
	this->active = active;
	if (active) {
		healthUpgrade->SetText(CreateUpgradeText("Extra live", currentHealthUpgrade, maxHealthUpgrades, costHealthUpgrade));
		speedUpgrade->SetText(CreateUpgradeText("Increase speed by 1", currentSpeedUpgrade, maxSpeedUpgrades, costSpeedUpgrade));
		damageUpgrade->SetText(CreateUpgradeText("Increase damage by 1", currentDamageUpgrade, maxDamageUpgrades, costDamageUpgrade));
	}
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

void Shop::Reset() {
	// reset the playerGold text
	std::string playerGoldString = "Gold: ";
	playerGoldString += std::to_string(player->GetGold());
	playerGold->SetText(playerGoldString);
	// reset inventory text
	if (player->IsInventoryFull()) {
		playerInventory->SetText("Inventory: full");
	}
	else {
		playerInventory->SetText("Inventory: empty");
	}
	// reset upgrades
	health = 4;
	currentHealthUpgrade = 0;
	healthUpgrade->SetText(CreateUpgradeText("Extra live", currentHealthUpgrade, maxHealthUpgrades, costHealthUpgrade));
	speed = 6.0f;
	currentSpeedUpgrade = 0;
	speedUpgrade->SetText(CreateUpgradeText("Increase speed by 1", currentSpeedUpgrade, maxSpeedUpgrades, costSpeedUpgrade));
	damage = 1;
	currentDamageUpgrade = 0;
	damageUpgrade->SetText(CreateUpgradeText("Increase damage by 1", currentDamageUpgrade, maxDamageUpgrades, costDamageUpgrade));
	// set active to false
	this->active = false;
}
