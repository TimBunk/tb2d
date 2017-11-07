#include "player.h"

Player::Player(Input* input, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Person::Person(rm, camera, shader, world) {
	this->input =  input;
	showCase = new ShowCase(700, 500, 50, 50, camera, rm->GetShader("hud"), rm->GetShader("textHud"), rm->GetTexture("showCase"));
	this->AddChild(showCase);
	item = nullptr;
	currentRoom = 0;
	gold = 0;
	std::string s = std::to_string(gold);
	std::string ss = "Gold: " + s;
	textGold = new Text("fonts/OpenSans-Regular.ttf", ss, 60, glm::vec4(0.62f, 0.62f, 0.62f, 1.0f), true, camera, rm->GetShader("textHud"));
	textGold->localPosition = glm::vec3(20, 100, 1.0f);
	this->AddChild(textGold);

	damage = 1.0f;
	currentDamage = damage;
	speed = 6.0f;
	currentSpeed = speed;
	attackSpeed = 0.333f;
	currentAttackSpeed = attackSpeed;
	sword = new Weapon(currentDamage, 135.0f, currentAttackSpeed, true, camera, shader, this->world);
	sword->GiveTexture(rm->GetTexture("playerSword"));
	sword->CreateBody(0, 0, 30, 60);
	this->AddChild(sword);
	health = 4;
	currentHealth = health;
	lastHealth = health;
	CreateLives(health);
	textStats = new Text("fonts/OpenSans-Regular.ttf", "No stats available", 22, glm::vec4(0.62f, 0.62f, 0.62f, 1.0f), true, camera, rm->GetShader("textHud"));
	textStats->localPosition = glm::vec3(20, 500, 1.0f);
	UpdateStats();
	this->AddChild(textStats);
}

Player::~Player() {
	delete sword;
	delete showCase;
	delete textGold;
	delete textStats;
	for (int i=0;i<health;i++) {
		delete hudHealth[i];
	}
}

void Player::Update(double deltaTime) {
	// TODO Stop updating player when it is not alive anymore

	// Set the player's movement
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (input->KeyDown(SDL_SCANCODE_W) || input->KeyDown(SDL_SCANCODE_UP)) {
		vel.y -= 1.0f;
	}
	if (input->KeyDown(SDL_SCANCODE_D) || input->KeyDown(SDL_SCANCODE_RIGHT)) {
		vel.x += 1.0f;
	}
	if (input->KeyDown(SDL_SCANCODE_S) || input->KeyDown(SDL_SCANCODE_DOWN)) {
		vel.y += 1.0f;
	}
	if (input->KeyDown(SDL_SCANCODE_A) || input->KeyDown(SDL_SCANCODE_LEFT)) {
		vel.x -= 1.0f;
	}
	// If left mouse click swing your sword
	if (input->MousePress(1)) {
		if (!sword->IsAttacking()) {
			sword->Attack();
		}
	}
	// If spacebar is pressed drink the potion and remove it from the showCase
	if (IsInventoryFull() && input->KeyPress(SDL_SCANCODE_SPACE)) {
		if (dynamic_cast<HealthPotion*>(item) != NULL) {
			this->ApplyHealing(dynamic_cast<HealthPotion*>(item)->Use());
		}
		else if (dynamic_cast<DamagePotion*>(item) != NULL) {
			this->damageBoost = dynamic_cast<DamagePotion*>(item)->Use();
		}
		else if (dynamic_cast<SpeedPotion*>(item) != NULL) {
			this->speedBoost = dynamic_cast<SpeedPotion*>(item)->Use();
		}
		showCase->Clear();
		item = nullptr;
	}
	// Set the velocity and the camera's position
	vel.Normalize();
	vel *= currentSpeed;
	body->SetLinearVelocity(vel);
	this->camera->SetPosition(glm::vec2(-this->GetPositionInPixels().x - -camera->screenWidth/2, -this->GetPositionInPixels().y - -camera->screenHeight/2));

	// Set the player's position
	this->localPosition.x = this->GetPositionInPixels().x;
	this->localPosition.y = this->GetPositionInPixels().y;
	this->localPosition.z = 5.0f;
	// FLIP the player's texture according to the mouse it's location
	if (input->GetMousePositionScreenSpace(camera).x > camera->screenWidth/2 && this->IsTextureFlipped()) {
		this->FlipTexture();
		sword->FlipBody();
	}
	else if (input->GetMousePositionScreenSpace(camera).x < camera->screenWidth/2 && !this->IsTextureFlipped()) {
		this->FlipTexture();
		sword->FlipBody();
	}

	// Get the mouse position in world space
	glm::vec2 mp = input->GetMousePositionWorldSpace(camera);
	// Calculate the angle between the mouse and piviot of the player
	glm::vec2 angle = mp - glm::vec2(this->GetPositionInPixels().x, this->GetPositionInPixels().y);
	// Normalize the angle
	angle = glm::normalize(angle);
	// Set the length of the angle to 40 pixels away from the player's piviot
	angle *= 40;
	sword->SetAngle(angle);
	sword->localPosition.x = angle.x;
	sword->localPosition.y = angle.y;

	// Update health textures
	if (lastHealth != currentHealth) {
		for (int i=0;i<health;i++) {
			if (currentHealth > i) {
				hudHealth[i]->SetTexture(rm->GetTexture("heartFilled"));
			}
			else {
				hudHealth[i]->SetTexture(rm->GetTexture("heartEmpty"));
			}
		}
	}
	lastHealth = currentHealth;

	// Update the stats of the player
	if (damageBoost.lifeTime > 0.0f) {
		damageBoost.lifeTime -= deltaTime;
		damageBoost.active = true;
		if (damageBoost.lifeTime <= 0.0f) {
			damageBoost.active = false;
		}
		sword->SetDamage(currentDamage);
	}
	if (speedBoost.lifeTime > 0.0f) {
		speedBoost.lifeTime -= deltaTime;
		speedBoost.active = true;
		if (speedBoost.lifeTime <= 0.0f) {
			speedBoost.active = false;
		}
		sword->SetAttackDuration(currentAttackSpeed);
	}
	UpdateStats();

	// Pick up items
	for (int i=0;i<contacts.size();i++) {
		// Check if the player already contains a item
		if (!IsInventoryFull()) {
			// Search for potions
			if (dynamic_cast<Potion*>(contacts[i]) != NULL) {
				GiveItem(dynamic_cast<Potion*>(contacts[i]));
			}
		}
		// If the contact is a item check if it is one of the below
		if (dynamic_cast<Item*>(contacts[i]) != NULL) {
			if (dynamic_cast<Bomb*>(contacts[i]) != NULL) {
				if (dynamic_cast<Bomb*>(contacts[i])->Impact()) {
					this->TakeDamage(1);
				}
			}
			else if (dynamic_cast<Gold*>(contacts[i]) != NULL) {
				AddGold(dynamic_cast<Gold*>(contacts[i])->GetGold());
			}
		}
	}
}

void Player::SetRoom(int number) {
	this->currentRoom = number;
}

int Player::GetRoom() {
	return currentRoom;
}

void Player::AddGold(int gold) {
	this->gold += gold;
	std::string s = std::to_string(this->gold);
	std::string ss = "Gold: " + s;
	textGold->SetText(ss);
}

int Player::GetGold() {
	return gold;
}

void Player::GiveItem(Item* item) {
	if (!IsInventoryFull()) {
		this->item = item;
		item->Destroy();
		showCase->Give(item->PickUp());
	}
}

bool Player::IsInventoryFull() {
	return showCase->IsFull();
}

void Player::UpgradeHealth(int newHealth) {
	this->health = newHealth;
	currentHealth++;
	this->CreateLives(health);
}

void Player::UpgradeSpeed(float newSpeed) {
	this->speed = newSpeed;
}

void Player::UpgradeDamage(int newDamage) {
	this->damage = newDamage;
	sword->SetDamage(this->damage);
}

void Player::UpdateStats() {
	// Create a text from the player's stats
	std::string stats = "PLAYER STATS \n";

	// Set the damage
	std::stringstream streamDamage;
	streamDamage << std::fixed << std::setprecision(1) << damage;
	std::string stringDamage;
	if (damageBoost.active) {
		std::stringstream streamDamageBoost;
		streamDamageBoost << std::fixed << std::setprecision(1) << damageBoost.value;
		std::stringstream streamDamageBoostTime;
		streamDamageBoostTime << std::fixed << std::setprecision(1) << damageBoost.lifeTime;
		stringDamage = streamDamage.str() + " + " + streamDamageBoost.str() + " for " + streamDamageBoostTime.str();
		currentDamage = damage + damageBoost.value;
	}
	else {
		stringDamage = streamDamage.str();
		currentDamage = damage;
	}
	stats += "Damage: " + stringDamage + "\n";

	// Set the attackSpeed and the speed
	std::stringstream streamAttackSpeed;
	streamAttackSpeed << std::fixed << std::setprecision(1) << attackSpeed;
	std::string stringAttackSpeed;
	std::stringstream streamSpeed;
	streamSpeed << std::fixed << std::setprecision(1) << speed;
	std::string stringSpeed;
	if (speedBoost.active) {
		std::stringstream streamAttackSpeedBoost;
		streamAttackSpeedBoost << std::fixed << std::setprecision(1) << speedBoost.attackSpeed;
		std::stringstream streamSpeedBoost;
		streamSpeedBoost << std::fixed << std::setprecision(1) << speedBoost.movemementSpeed;
		std::stringstream streamAttackSpeedBoostTime;
		streamAttackSpeedBoostTime << std::fixed << std::setprecision(1) << speedBoost.lifeTime;

		stringAttackSpeed = streamAttackSpeed.str() + " + " + streamAttackSpeedBoost.str() + " for " + streamAttackSpeedBoostTime.str();
		stringSpeed = streamSpeed.str() + " + " + streamSpeedBoost.str() + " for " + streamAttackSpeedBoostTime.str();
		currentAttackSpeed = attackSpeed + speedBoost.attackSpeed;
		currentSpeed = speed + speedBoost.movemementSpeed;
	}
	else {
		stringAttackSpeed = streamAttackSpeed.str();
		stringSpeed = streamSpeed.str();
		currentAttackSpeed = attackSpeed;
		currentSpeed = speed;
	}
	stats += "AttackSpeed: " + stringAttackSpeed + "\n";
	stats += "Speed: " + stringSpeed + "\n";

	textStats->SetText(stats);
}

void Player::CreateLives(int amount) {
	// Delete the old hearts
	std::vector<Hud*>::iterator it = hudHealth.begin();
	while (it != hudHealth.end()) {
		this->RemoveChild((*it));
		delete (*it);
		it = hudHealth.erase(it);
	}
	// Create the health hearts
	int xHealth = 30;
	for (int i=0;i<amount;i++) {
		hudHealth.push_back(new Hud(xHealth, 30, 50, 50, camera, rm->GetShader("hud"), rm->GetTexture("heartFilled")));
		if (currentHealth-1 < i) {
			hudHealth[i]->SetTexture(rm->GetTexture("heartEmpty"));
		}
		this->AddChild(hudHealth[i]);
		xHealth += 60;
	}
}

void Player::Reset() {
	health = 4;
	currentHealth = 4;
	lastHealth = currentHealth;
	CreateLives(4);
	UpgradeDamage(1);
	speed = 6.0f;
	this->localPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	body->SetTransform(b2Vec2(0.0f, 0.0f), this->angle);
	SetRoom(0);
	showCase->Clear();
	item = nullptr;
	AddGold(GetGold() * -1);
}
