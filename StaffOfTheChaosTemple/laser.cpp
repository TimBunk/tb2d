#include "laser.h"
#include "mirror.h"

Laser::Laser(b2World* world, Shader* debug, float radius, Texture* texture, Shader* shader, Camera* camera, bool HUD) : Sprite::Sprite(texture, shader, camera, HUD)
{
	this->world = world;
	reflection = b2Vec2(0.0f, 0.0f);
	raycast = new RaycastCallBack();
	raycast->CreateLine(2500.0f, 50.0f, camera, debug, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	direction = glm::vec2(0.0f, 0.0f);
	width = 25.0f;
	height = radius;
	//this->CreateBody(radius, 25.0f, glm::vec2(0.0f, (radius / 2 * -1)));
	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Laser::~Laser()
{
	delete raycast;
}

void Laser::Update(double deltaTime)
{
	// Draw the ray's direction and length
	raycast->ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	raycast->Draw(localPosition, glm::atan(-direction.y, -direction.x));

	// Shoot raycast
	b2Vec2 globalPos = b2Vec2(localPosition.x * B2Entity::p2m, localPosition.y * B2Entity::p2m);
	b2Vec2 destination = globalPos + b2Vec2(direction.x * B2Entity::p2m, direction.y * B2Entity::p2m);
	world->RayCast(raycast, globalPos, destination);
	RaycastOutput ro = raycast->GetOutput();

	if (ro.fixture != nullptr) {
		if (dynamic_cast<Mirror*>(static_cast<B2Entity*>(ro.fixture->GetUserData())) != NULL) {
			hit = true;
			hitPosition = ro.point;
			// intersectionPoint is a vector from the ray's starting point and the hitted point
			b2Vec2 intersectionPoint = globalPos - destination;
			intersectionPoint *= ro.fraction;

			// Calculation reflection = d-(2*dot(d-n)*n)
			reflection = intersectionPoint - (2 * b2Dot(intersectionPoint, ro.normal) * ro.normal);
			// Draw the reflection
			raycast->ChangeColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			raycast->Draw(glm::vec2(ro.point.x * B2Entity::m2p, ro.point.y * B2Entity::m2p), glm::atan(reflection.y, reflection.x));

			// Draw the normal
			raycast->ChangeColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
			raycast->Draw(glm::vec2((ro.point.x + ro.normal.x) * B2Entity::m2p, (ro.point.y + ro.normal.y) * B2Entity::m2p), glm::atan(ro.normal.y, ro.normal.x));
		}
		else {
			hit = false;
		}
		// Scale the laser by the distance of hit
		localScale.y = ro.fraction;
	}
	else {
		hit = false;
		hitPosition = b2Vec2(0.0f, 0.0f);
		reflection = b2Vec2(0.0f, 0.0f);
		localScale.y = 1.0f;
	}
}

void Laser::Draw()
{
	// Update VBO
	GLfloat vertices[6][4] = {
		// Vertex positions		// uv positions
		{ -width/2.0f, 0.0f,	0.0f, 0.0f }, // lower left
		{ width/2.0f, 0.0f,		1.0f, 0.0f }, // lower right
		{ -width/2.0f, -height,	0.0f, localScale.y * height / width }, // top left

		{ width/2.0f, 0.0f,		1.0f, 0.0f }, // lower right
		{ width/2.0f, -height,	1.0f, localScale.y * height / width }, // top right
		{ -width/2.0f, -height,	0.0f, localScale.y * height / width }, // top left
	};
	glBindVertexArray(VAO);
	// Update content of VBO memory
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->Use();
	shader->SetMatrix4("projection", camera->GetProjectionMatrix());
	shader->SetMatrix4("view", camera->GetViewMatrix());
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(localPosition.x, localPosition.y, 0.0f));
	model = glm::rotate(model, localAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(localScale.x, localScale.y, 1.0f));
	shader->SetMatrix4("model", model);
	glActiveTexture(GL_TEXTURE0 + texture->GetId());
	shader->SetInt("ourTexture", texture->GetId());
	glBindTexture(GL_TEXTURE_2D, texture->GetId());
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Laser::SetDirection(glm::vec2 direction)
{
	this->direction = direction;
}

bool Laser::Hit()
{
	return hit;
}

glm::vec2 Laser::GetHitPosition()
{
	glm::vec2 hp = glm::vec2(hitPosition.x * B2Entity::m2p, hitPosition.y * B2Entity::m2p);
	return hp;
}

glm::vec2 Laser::GetReflection()
{
	glm::vec2 reflect = glm::vec2(reflection.x * B2Entity::m2p, reflection.y * B2Entity::m2p);
	return reflect;
}
