#include "staff.h"

Staff::Staff(float damage, float laserRange, int width, int height, unsigned int textureID, b2World* world) : Sprite::Sprite(width, height, textureID)
{
	// Initialize the variables
	this->damage = damage;
	this->laserRange = laserRange;
	this->world = world;
	// In order to make the lasers work we need atleast one already in the vector
	lasers.push_back(new Laser(damage, 10, laserRange, 0, world));
	lasers[0]->SetPivot(glm::vec2(0.0f, -0.5f));
	shooting = false;
}

Staff::~Staff()
{
	// Delete the allocated memory
	std::vector<Laser*>::iterator it = lasers.begin();
	while (it != lasers.end()) {
		delete (*it);
		it = lasers.erase(it);
	}
}

void Staff::Update(double deltaTime)
{
	// Draw the particles of the lasers
	for (int i = 0; i < lasers.size(); i++) {
		lasers[i]->DrawParticles(deltaTime);
	}
	if (shooting) {
		shooting = false;
		float angleStaff = GetGlobalAngle();
		glm::vec2 direction;
		direction.x = glm::cos(angleStaff);
		direction.y = glm::sin(angleStaff);
		direction = glm::normalize(direction);
		direction *= laserRange;
		direction = direction * -1.0f;
		lasers[0]->localPosition = this->GetGlobalPosition();
		lasers[0]->localAngle = this->GetGlobalAngle() - (90.0f * M_PI / 180.0f);
		lasers[0]->SetDirection(direction);
		lasers[0]->Update(deltaTime);
		lasers[0]->UpdateChilderen(NULL, deltaTime);
		lasers[0]->Draw();
		// Check if the first laser hits
		int i = 1;
		if (lasers[0]->Hit()) {
			while (i <= lasers.size()) {
				// If the latest laser has a hit create a new one
				if (i == lasers.size() && lasers[i - 1]->Hit() && i < 15) {
					lasers.push_back(new Laser(damage, 10, laserRange, 0, world));
					lasers[i]->SetPivot(glm::vec2(0.0f, -0.5f));
					direction = lasers[i - 1]->GetReflection();
					direction = glm::normalize(direction);
					direction *= laserRange;
					direction = direction * -1.0f;
					lasers[i]->SetDirection(direction);
					lasers[i]->localAngle = glm::atan(direction.y * -1, direction.x * -1) - (90.0f * M_PI / 180.0f);
					lasers[i]->localPosition = lasers[i - 1]->GetHitPosition();
					lasers[i]->Update(deltaTime);
					lasers[i]->UpdateChilderen(NULL, deltaTime);
					lasers[i]->Draw();
				}
				// Update and draw the lasers that already exist
				else if (lasers[i - 1]->Hit() && i < 15) {
					direction = lasers[i - 1]->GetReflection();
					direction = glm::normalize(direction);
					direction *= laserRange;
					direction = direction * -1.0f;
					lasers[i]->SetDirection(direction);
					lasers[i]->localAngle = glm::atan(direction.y * -1, direction.x * -1) - (90.0f * M_PI / 180.0f);
					lasers[i]->localPosition = lasers[i - 1]->GetHitPosition();
					lasers[i]->Update(deltaTime);
					lasers[i]->UpdateChilderen(NULL, deltaTime);
					lasers[i]->Draw();
				}
				// If a laser does not hit anything delete every laser that comes after it
				else if (i > 0 && lasers[i - 1]->Hit() == false) {
					//int j = lasers.size();
					while (lasers.size() > i) {
						delete lasers[lasers.size() - 1];
						lasers.pop_back();
					}
					// Break out of the while loop
					break;
				}
				i++;
				// 15 are the maximum allowed of lasers
				if (lasers.size() > 15) {
					while (lasers.size() > 15) {
						delete lasers[lasers.size() - 1];
						lasers.pop_back();
					}
					// Break out of the while loop
					break;
				}
			}
		}
	}
}