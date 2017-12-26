#include "level.h"

Level::Level(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	finish = nullptr;
	finished = false;

	contactListener = new ContactListener();
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);

	player = new Player(camera, 10, 10.0f, 1, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
	player->CreateCircleCollider(40.0f, true, false);
	player->SetDebugColor(glm::vec3(1, 0, 0));
}

Level::~Level()
{
	delete finish;
	delete player;
	delete world;
	delete contactListener;
}

void Level::Update(double deltaTime)
{
	if (finish->Contact(player)) {
		std::cout << "FINISH" << std::endl;
		finished = true;
	}
	world->Step(deltaTime, 8, 3);
}

bool Level::IsFinished()
{
	if (finished) {
		finished = false;
		return true;
	}
	return false;
}

b2World * Level::GetB2World()
{
	return world;
}

void Level::CreateFinish(int x, int y, int width, int height)
{
	finish = new B2Entity(width, height, 0, world);
	finish->localPosition = glm::vec2(x, y);
	finish->CreateBoxCollider(width, height, glm::vec2(0, 0), false, true);
	finish->SetDebugColor(glm::vec3(0, 1, 0));
	this->AddChild(finish);
	world->SetContactListener(contactListener);
	AddChild(player);
}
