#include "level.h"

Level::Level(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	finish = nullptr;
	finished = false;

	redHealthbarPlayer = new Sprite(350, 75, 0);
	redHealthbarPlayer->SetColor(glm::vec4(1, 0, 0, 1));
	redHealthbarPlayer->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	redHealthbarPlayer->localPosition = glm::vec2(-860, -425);
	redHealthbarPlayer->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(redHealthbarPlayer);
	greenHealthbarPlayer = new Sprite(350, 75, 0);
	greenHealthbarPlayer->SetColor(glm::vec4(0, 1, 0, 1));
	greenHealthbarPlayer->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	greenHealthbarPlayer->localPosition = glm::vec2(-860, -425);
	greenHealthbarPlayer->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(greenHealthbarPlayer);

	contactListener = new ContactListener();
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);

	player = new Player(camera, 800.0f, 10.0f, 50.0f, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
	player->CreateCircleCollider(40.0f, true, false);
	player->SetDebugColor(glm::vec3(1, 0, 0));
}

Level::~Level()
{
	delete greenHealthbarPlayer;
	delete redHealthbarPlayer;
	delete finish;
	delete player;

	std::vector<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		delete (*it);
		it = enemies.erase(it);
	}

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
	Draw();
	greenHealthbarPlayer->SetWidth(player->GetCurrentHealth()/player->GetMaxHealth() * 350);

	// Check if the enmies are alive otherwise remove them
	std::vector<Enemy*>::iterator it = enemies.begin();
	while (it != enemies.end()) {
		if ((*it)->IsAlive() == false) {
			RemoveChild((*it));
			(*it)->Die();
			it = enemies.erase(it);
		}
		else {
			++it;
		}
	}

	/*b2Body* bodylist = world->GetBodyList();
	glm::vec2 _mousePos = Input::GetMousePositionWorldSpace(camera);
	b2Vec2 mousePos = b2Vec2(_mousePos.x * B2Entity::p2m, _mousePos.y * B2Entity::p2m);

	while (bodylist != NULL) {
		if (bodylist->GetFixtureList()->TestPoint(mousePos)) {
			std::cout << "hit is true!" << std::endl;
		}
		bodylist = bodylist->GetNext();
	}*/
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

void Level::AddEnemy(Enemy * enemy)
{
	enemies.push_back(enemy);
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
