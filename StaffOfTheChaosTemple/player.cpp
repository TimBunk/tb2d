#include "player.h"

Player::Player(Input* input, int health, float speed, int damage, Camera * camera, b2World * world) : Person::Person(health, speed, damage, camera, world)
{
	this->input = input;
	staff = new Staff(1000.0f, world, 100, 200, ResourceManager::GetTexture("staff"), camera);
	staff->CreateBody(200, 100, glm::vec2(0.0f, -50.0f));
	staff->localAngle = (90.0f * M_PI / 180.0f);//(90.0f * M_PI / 180.0f);
	this->AddChild(staff);
}

Player::~Player()
{
	delete staff;
}

void Player::Update(double deltaTime)
{
	// If mouse down start shooting a laser
	if (input->MouseDown(GLFW_MOUSE_BUTTON_1)) {
		staff->Shoot();
	}
	// Movement player
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	if (input->KeyDown(GLFW_KEY_W) || input->KeyDown(GLFW_KEY_UP)) {
		velocity.y += 1.0f;
	}
	if (input->KeyDown(GLFW_KEY_S) || input->KeyDown(GLFW_KEY_DOWN)) {
		velocity.y += -1.0f;
	}
	if (input->KeyDown(GLFW_KEY_A) || input->KeyDown(GLFW_KEY_LEFT)) {
		velocity.x += -1.0f;
	}
	if (input->KeyDown(GLFW_KEY_D) || input->KeyDown(GLFW_KEY_RIGHT)) {
		velocity.x += 1.0f;
	}
	// The velocity has to be not equal to zero otherwise if I normalze the vec2 it will return nand-id
	if (velocity.x != 0 || velocity.y != 0) {
		velocity = glm::normalize(velocity);
		velocity *= 10.0f;
	}
	localPosition = ApplyVelocityB2body(velocity);
	camera->SetPosition(glm::vec2(GetGlobalPosition().x - camera->GetWidth()/2, GetGlobalPosition().y - camera->GetHeight()/2));
	// Rotate the player towards the mouse
	glm::vec2 direction = input->GetMousePositionWorldSpace(camera) - GetGlobalPosition();
	glm::normalize(direction);
	this->localAngle = std::atan2(direction.y, direction.x);
	//std::cout << " player angle = " << (glm::atan(direction.y, direction.x) * 180.0f / M_PI) << std::endl;

	// Rotate the staff towards the mouse
	glm::vec2 directionStaff = (input->GetMousePositionWorldSpace(camera) - staff->GetGlobalPosition());
	glm::normalize(directionStaff);
	staff->localAngle = std::atan2(directionStaff.y, directionStaff.x) + (90.0f * M_PI / 180.0f) - this->localAngle; //(90.0f * M_PI / 180.0f);
	// Limit the angle to not go lower then 45 degrees
	if (staff->localAngle < M_PI_4) {
		staff->localAngle = M_PI_4;
	}
	// std::cout << " staff angle = " << staff->localAngle * 180.f / M_PI << std::endl;
	staff->localPosition = glm::vec2(0.0f, 120.0f);

	for (int i = 0; i < contacts.size(); i++) {
		//std::cout << "contact amount = " << contacts.size() << std::endl;
		if (dynamic_cast<Rotator*>(contacts[i]) != NULL) {
			// Get the pointer of the rotator
			Rotator* rot = dynamic_cast<Rotator*>(contacts[i]);

			// Position 'a' is the pivot point of the rotator, The reason I do minus 0.0001f is because otherwise the value will be zero and normaling zero will return nan-id
			glm::vec2 a = (glm::vec2(rot->GetGlobalPosition().x - 0.001f, rot->GetGlobalPosition().y) - rot->GetGlobalPosition());
			a = glm::normalize(a);
			// Position 'b' is the the position from the player relative to the pivot point from the rotator
			glm::vec2 b = GetGlobalPosition() - rot->GetGlobalPosition();
			b = glm::normalize(b);

			// Dot product between pivot rotator and player
			float dot = glm::dot(a, b);//      # dot product
			//angle = atan2(det, dot)  # atan2(y, x) or atan2(sin, cos)
			float det = a.x*b.y - a.y*b.x;//      # determinant

			float anglePlayer = (glm::atan(det, dot) * 180.0f / M_PI);//(glm::acos(glm::dot(a, b)) * 180.0f / M_PI);
			//std::cout << " angle player = " << anglePlayer << std::endl;
			float angleRot = (rot->GetRotation() * 180.0f / M_PI);
			//std::cout << " angle rotator = " << angleRot << std::endl;
			float difference = anglePlayer - angleRot;
			//std::cout << " difference = " << anglePlayer - angleRot << std::endl;

			// Rotate the mirror's rotator
			// Sometimes there is a huge difference betweent the angle of the player and the rotator
			// so a hacky kinda way is: asking if it higher or lower helps me find out of what side the player is pushing from
			if (difference > -250.0f && difference < 0.0f || difference > 250.0f) {
				rot->Rotate(true, (50.0f * deltaTime));
			}
			else if (difference >= 0.0f || difference < -250.0f) {
				rot->Rotate(false, (50.0f * deltaTime));
			}
		}
	}
}

void Player::SetCamera(Camera * camera)
{
	this->camera = camera;
	staff->SetCamera(camera);
}
