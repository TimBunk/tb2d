#include "level.h"

Level::Level(int screenWidthCamera, int screenHeightCamera, std::string filename) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	player = nullptr;
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
	world->SetContactListener(contactListener);

	LoadingErrors = "";
	textfile = new Textfile();
	Load(filename);
}

Level::~Level()
{
	std::vector<Entity*>::iterator itLevelObjects = levelObjects.begin();
	while (itLevelObjects != levelObjects.end()) {
		delete (*itLevelObjects);
		itLevelObjects = levelObjects.erase(itLevelObjects);
	}

	delete textfile;
	delete greenHealthbarPlayer;
	delete redHealthbarPlayer;
	if (player != nullptr) {
		delete finish;
		delete player;
	}

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
			delete (*it);
			it = enemies.erase(it);
		}
		else {
			++it;
		}
	}
}

bool Level::IsFinished()
{
	if (finished) {
		finished = false;
		return true;
	}
	return false;
}

void Level::Load(std::string filename)
{
	if (textfile->Open(filename.c_str())) {
		textfile->StartReading();
		while (!textfile->EndOfFile()) {
			std::string lineoftext = textfile->ReadLine();
			// FLOOR
			if (lineoftext[0] == 'f' && lineoftext[1] == 'l') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				float _height;
				sscanf(lineoftext.c_str(), "floor %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width, &_height);
				Sprite* _floor = new Sprite(_width, _height, ResourceManager::GetTexture("floor")->GetId());
				_floor->localPosition = _pos;
				_floor->localAngle = _angle;
				_floor->SetRepeatableUV(glm::vec2(_floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
				AddChild(_floor);
				levelObjects.push_back(_floor);
			}
			// WALL
			else if (lineoftext[0] == 'w') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				sscanf(lineoftext.c_str(), "wall %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width);
				B2Entity* _wall = new B2Entity(_width, 750, ResourceManager::GetTexture("wall")->GetId(), world);
				_wall->CreateBoxCollider(_width, 100, glm::vec2(0.0f, 0.0f), false, false);
				_wall->localPosition = _pos;
				_wall->localAngle = _angle;
				_wall->SetRepeatableUV(glm::vec2(_wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
				AddChild(_wall);
				levelObjects.push_back(_wall);
			}
			// MIRROR
			else if (lineoftext[0] == 'm') {
				glm::vec2 _pos;
				float _angle;
				int _rotatable;
				sscanf(lineoftext.c_str(), "mirror %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_rotatable);
				Mirror* _mirror = new Mirror(_rotatable, 150.0f, 150.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
				_mirror->CreateBoxCollider(100.0f, 110.0f, glm::vec2(0.15f, 0.0f), false, false);
				_mirror->localPosition = _pos;
				_mirror->SetRotation(glm::degrees(_angle));
				_mirror->localAngle = _angle;

				AddChild(_mirror);
				levelObjects.push_back(_mirror);
			}
			// CRYSTAL
			else if (lineoftext[0] == 'c') {
				glm::vec2 _pos;
				float _angle;
				float uniqueID;
				sscanf(lineoftext.c_str(), "crystal %f %f %f %f", &_pos.x, &_pos.y, &_angle, &uniqueID);
				Crystal* _crystal = new Crystal(uniqueID, 70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
				_crystal->CreateBoxCollider(70, 70, glm::vec2(0.0f, 0.0f), false, false);
				_crystal->localPosition = _pos;
				_crystal->localAngle = _angle;
				AddChild(_crystal);
				levelObjects.push_back(_crystal);
				tmpCrystals.push_back(_crystal);
			}
			// DOOR
			else if (lineoftext[0] == 'd') {
				glm::vec2 _pos;
				float _angle;
				float _crystals;
				sscanf(lineoftext.c_str(), "door %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_crystals);
				Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
				_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
				_door->localPosition = _pos;
				_door->localAngle = _angle;
				AddChild(_door);
				levelObjects.push_back(_door);
				Link link;
				link.door = _door;
				for (int i = 0; i < _crystals; i++) {
					lineoftext = textfile->ReadLine();
					int _crystalid;
					sscanf(lineoftext.c_str(), "%d", &_crystalid);
					link.crystalIDs.push_back(_crystalid);
				}
				tmpLinks.push_back(link);
			}
			// ENEMY
			else if (lineoftext[0] == 'e') {
				glm::vec2 _pos;
				float _angle;
				float _health;
				float _damage;
				float _speed;
				float _LOS;//LOS short for LineOfSight
				sscanf(lineoftext.c_str(), "enemy %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_speed, &_damage, &_LOS);
				Enemy* _enemy = new Enemy(NULL, _LOS, 0.6f, 0.5f, _health, _speed, _damage, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
				_enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
				_enemy->localPosition = _pos;
				_enemy->localAngle = _angle;
				AddChild(_enemy);
				enemies.push_back(_enemy);
			}
			// PLAYER
			else if (lineoftext[0] == 'p') {
				glm::vec2 _pos;
				float _angle;
				float _health;
				float _damage;
				float _speed;
				sscanf(lineoftext.c_str(), "player %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_damage, &_speed);
				player = new Player(camera, _health, _speed, _damage, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
				player->CreateCircleCollider(40.0f, true, false);
				player->localPosition = _pos;
				player->localAngle = _angle;
				//player->Update(0);
				player->UpdateChilderen(this, 0);
				AddChild(player);
			}
			// FINISH
			else if (lineoftext[0] == 'f' && lineoftext[1] == 'i') {
				glm::vec2 _pos;
				float _angle;
				float _width;
				float _height;
				sscanf(lineoftext.c_str(), "finish %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width, &_height);
				finish = new B2Entity(_width, _height, 0, world);
				finish->CreateBoxCollider(_width, _height, glm::vec2(0, 0), true, true);
				finish->localPosition = _pos;
				finish->localAngle = _angle;
				AddChild(finish);
			}
		}
		textfile->Close();
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->SetPlayer(player);
			enemies[i]->UpdateChilderen(this, 0);
			enemies[i]->Init();
		}
		for (int i = 0; i < tmpLinks.size(); i++) {
			for (int j = 0; j < tmpLinks[i].crystalIDs.size(); j++) {
				for (int k = 0; k < tmpCrystals.size(); k++) {
					if (tmpLinks[i].crystalIDs[j] == tmpCrystals[k]->GetUniqueID()) {
						tmpLinks[i].door->Link(tmpCrystals[k]);
					}
				}
			}
		}
		tmpLinks.clear();
		tmpCrystals.clear();
	}
	else {
		LoadingErrors = "Could not find: " + filename;
	}
}