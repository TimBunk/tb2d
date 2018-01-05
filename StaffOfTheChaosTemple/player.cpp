#include "player.h"

Player::Player(Camera* camera, float health, float speed, float damage, int width, int height, unsigned int textureID, b2World* world) : Person::Person(health, speed, damage, width, height, textureID, world)
{
	this->camera = camera;
	staff = new Staff(damage, 1000.0f, 100, 200, ResourceManager::GetTexture("staff")->GetId(), world);
	staff->localPosition.x = -25;
	staff->localPosition.y = -50;
	this->AddChild(staff);
}

Player::~Player()
{
	delete staff;
}

void Player::Update(double deltaTime)
{
	// If mouse down start shooting a laser
	if (Input::MouseDown(GLFW_MOUSE_BUTTON_1)) {
		staff->Shoot();
	}
	// Movement player
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
	if (Input::KeyDown(GLFW_KEY_W) || Input::KeyDown(GLFW_KEY_UP)) {
		velocity.y += 1.0f;
	}
	if (Input::KeyDown(GLFW_KEY_S) || Input::KeyDown(GLFW_KEY_DOWN)) {
		velocity.y += -1.0f;
	}
	if (Input::KeyDown(GLFW_KEY_A) || Input::KeyDown(GLFW_KEY_LEFT)) {
		velocity.x += -1.0f;
	}
	if (Input::KeyDown(GLFW_KEY_D) || Input::KeyDown(GLFW_KEY_RIGHT)) {
		velocity.x += 1.0f;
	}
	// The velocity has to be not equal to zero otherwise if I normalze the vec2 it will return nand-id
	if (velocity.x != 0 || velocity.y != 0) {
		velocity = glm::normalize(velocity);
		velocity *= 10.0f;
	}
	localPosition = ApplyVelocityB2body(velocity);
	camera->SetPosition(GetGlobalPosition());
	// Rotate the player towards the mouse
	glm::vec2 mousePos = Input::GetMousePositionWorldSpace();
	glm::vec2 direction = mousePos - GetGlobalPosition();
	this->localAngle = std::atan2(direction.y, direction.x) + glm::radians(180.0f);
	// Rotate the staff towards the mouse
	glm::vec2 dirStaff = mousePos - glm::vec2(staff->GetGlobalPosition().x, staff->GetGlobalPosition().y);
	staff->localAngle = glm::atan(dirStaff.y, dirStaff.x) - localAngle + glm::radians(180.0f);
	// There is a issue where sometimes the angle goes to a really high number and doing -360.0f fixes it from going to high
	if (glm::degrees(staff->localAngle) > 10.0f) {
		staff->localAngle = glm::radians(glm::degrees(staff->localAngle) - 360.0f);
	}
	// The angle of the staff cant go any lower then -35 degrees otherwise the player will hit itself
	if (glm::degrees(staff->localAngle) < -35.0f) {
		staff->localAngle = glm::radians(-35.0f);
	}

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