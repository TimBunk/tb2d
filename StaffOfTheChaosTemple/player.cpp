#include "player.h"

Player::Player(Input* input, ResourceManager* rm, Camera * camera, Shader * shader, b2World * world) : B2Entity::B2Entity(camera, shader, world)
{
	this->input = input;
	this->rm = rm;
	staff = new Staff(1000.0f, world, rm, 50, 150, rm->GetTexture("staff"), rm->GetShader("defaultShader"), camera);
	staff->localAngle = (90.0f * M_PI / 180.0f);//(90.0f * M_PI / 180.0f);
	this->AddChild(staff);
}

Player::~Player()
{
	delete staff;
}

void Player::Update(double deltaTime)
{
	if (input->MouseDown(GLFW_MOUSE_BUTTON_1)) {
		staff->Shoot();
	}

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
	body->SetAwake(true);
	// The velocity has to be not equal to zero otherwise if I normalze the vec2 it will return nand-id
	if (velocity.x != 0 || velocity.y != 0) {
		velocity = glm::normalize(velocity);
		velocity *= 10.0f;
		localPosition = ApplyVelocityB2body(velocity);
	}
	// Rotate the player towards the mouse
	glm::vec2 direction = input->GetMousePositionWorldSpace(camera) - GetGlobalPosition();
	glm::normalize(direction);
	this->localAngle = std::atan2(direction.y, direction.x);
	std::cout << " angle = " << (localAngle * 180.0f / M_PI) << std::endl;

	staff->localAngle = (90.0f * M_PI / 180.0f);

	staff->localPosition.x = glm::cos(staff->localAngle + localAngle);
	staff->localPosition.y = glm::sin(staff->localAngle + localAngle);
	staff->localPosition = glm::normalize(staff->localPosition);
	staff->localPosition *= 200.0f;
}

void Player::SetCamera(Camera * camera)
{
	this->camera = camera;
}
