#include "player.h"

Player::Player(PlayerHud* playerHud, Input* input, ResourceManager* rm, Camera* camera, Shader* shader, b2World* world) : Person::Person(rm, camera, shader, world) {
	// Initialize all of the variables
	this->playerHud = playerHud;
	this->AddChild(playerHud);
	this->input =  input;
	item = nullptr;
	currentRoom = 0;
	gold = 0;

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
	this->playerHud->CreateLives(currentHealth, health);
	UpdateStats();
}

Player::~Player() {
	delete sword;
}

void Player::Update(double deltaTime) {
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
		playerHud->ClearShowcase();
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
		playerHud->UpdateHealth(currentHealth);
	}
	lastHealth = currentHealth;

	// Check if the person got damaged
	if (damaged && timerDamaged < cooldownDamaged) {
		timerDamaged += deltaTime;
	}
	else {
		timerDamaged = 0.0f;
		damaged = false;
	}

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
	for (unsigned int i=0;i<contacts.size();i++) {
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
	// Add to the player's gold and update the text that displays the amount of gold
	this->gold += gold;
	playerHud->UpdateGold(this->gold);
}

int Player::GetGold() {
	return gold;
}

void Player::GiveItem(Item* item) {
	// Item will only be added if the inventory is empty
	if (!IsInventoryFull()) {
		this->item = item;
		item->Destroy();
		playerHud->GiveShowcase(item->PickUp());
	}
}

bool Player::IsInventoryFull() {
	return playerHud->IsShowCaseFull();
}

void Player::UpgradeHealth(int newHealth) {
	this->health = newHealth;
	currentHealth++;
	playerHud->CreateLives(currentHealth, health);
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
	playerHud->UpdateStats(stats);
}

void Player::Reset() {
	// Reset all of the player's variables
	health = 4;
	currentHealth = 4;
	lastHealth = currentHealth;
	playerHud->CreateLives(currentHealth, health);
	UpgradeDamage(1);
	speed = 6.0f;
	this->localPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	body->SetTransform(b2Vec2(0.0f, 0.0f), this->angle);
	SetRoom(0);
	playerHud->ClearShowcase();
	item = nullptr;
	AddGold(GetGold() * -1);
}
