#include "player.h"

Player::Player(Input* input, Camera* camera, ResourceManager* rm, Shader* shader, b2World* world) : Person::Person(camera, shader) {
	this->input =  input;
	this->rm = rm;
	sword = new Weapon(1.0f, 135.0f, 0.25f, true, camera, shader);
	sword->GiveTexture(rm->GetTexture("playerSword"));
	sword->CreateBody(0, 0, 30, 60, world);
	this->AddChild(sword);
	showCase = new ShowCase(700, 500, 50, 50, camera, rm->GetShader("hud"), rm->GetTexture("showCase"));
	this->AddChild(showCase);
	potion = nullptr;
	currentRoom = 0;
	gold = 0;
	std::string s = std::to_string(gold);
	std::string ss = "Gold: " + s;
	textGold = new Text("fonts/OpenSans-Regular.ttf", ss, 60, glm::vec4(0.62f, 0.62f, 0.62f, 1.0f), true, camera, rm->GetShader("textHud"));
	textGold->localPosition = glm::vec3(20, 100, 1.0f);
	this->AddChild(textGold);
	// Create the health hearts
	health = 4;
	currentHealth = health;
	lastHealth = health;
	int xHealth = 30;
	for (int i=0;i<health;i++) {
		hudHealth.push_back(new Hud(xHealth, 30, 50, 50, camera, rm->GetShader("hud"), rm->GetTexture("heartFilled")));
		this->AddChild(hudHealth[i]);
		xHealth += 60;
	}
}

Player::~Player() {
	delete sword;
	delete showCase;
	delete textGold;
	for (int i=0;i<health;i++) {
		delete hudHealth[i];
	}
}

void Player::Update(float deltaTime) {

	// Set the player's movement
	float speed = 2000.0f * deltaTime;
	b2Vec2 vel = b2Vec2(0.0f, 0.0f);
	if (input->KeyDown(SDL_SCANCODE_W) || input->KeyDown(SDL_SCANCODE_UP)) {
		vel.y -= speed;
	}
	if (input->KeyDown(SDL_SCANCODE_D) || input->KeyDown(SDL_SCANCODE_RIGHT)) {
		vel.x += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_S) || input->KeyDown(SDL_SCANCODE_DOWN)) {
		vel.y += speed;
	}
	if (input->KeyDown(SDL_SCANCODE_A) || input->KeyDown(SDL_SCANCODE_LEFT)) {
		vel.x -= speed;
	}
	// If spacebar is pressed drink the potion and remove it from the showCase
	if (showCase->IsFull() && input->KeyPress(SDL_SCANCODE_SPACE)) {
		if (dynamic_cast<HealthPotion*>(potion) != NULL) {
			this->ApplyHealing(dynamic_cast<HealthPotion*>(potion)->Use());
		}
		potion->Use(this);
		showCase->Clear();
		potion = nullptr;
	}
	// If left mouse click swing your sword
	if (input->MousePress(1)) {
		if (!sword->IsAttacking()) {
			sword->Attack();
			std::cout << "Mouse clicked" << std::endl;
		}
	}
	if (input->KeyPress(SDL_SCANCODE_K)) {
		this->TakeDamage(1);
	}
	// Set the velocity and the camera's position
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


	// Pick up items
	for (int i=0;i<contacts.size();i++) {
		// Search for potions if there are none in the showCase already
		if (!showCase->IsFull()) {
			if (dynamic_cast<Potion*>(contacts[i]) != NULL) {
				this->potion = dynamic_cast<Potion*>(contacts[i]);
				potion->Destroy();
				showCase->Give(potion->PickUp());
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
	std::string s = std::to_string(gold);
	std::string ss = "Gold: " + s;
	textGold->SetText(ss);
}
