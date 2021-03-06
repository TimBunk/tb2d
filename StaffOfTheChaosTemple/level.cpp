#include "level.h"

Level::Level(int screenWidthCamera, int screenHeightCamera) : Scene::Scene(screenWidthCamera, screenHeightCamera)
{
	// Initialize variables
	player = nullptr;
	finish = nullptr;
	finished = false;
	// Create healthbar player
	Text* health = new Text("health", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::centerY);
	health->localPosition = glm::vec2(-1700, -700);
	AddChild(health);
	textVector.push_back(health);
	redHealthbarPlayer = new Sprite(700, 150, 0);
	redHealthbarPlayer->SetColor(glm::vec4(1, 0, 0, 1));
	redHealthbarPlayer->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	redHealthbarPlayer->localPosition = glm::vec2(-1720, -850);
	redHealthbarPlayer->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(redHealthbarPlayer);
	greenHealthbarPlayer = new Sprite(700, 150, 0);
	greenHealthbarPlayer->SetColor(glm::vec4(0, 1, 0, 1));
	greenHealthbarPlayer->SetRenderer(RenderManager::GetSimpleRenderer("hud"));
	greenHealthbarPlayer->localPosition = glm::vec2(-1720, -850);
	greenHealthbarPlayer->SetPivot(glm::vec2(0.5f, 0.0f));
	AddChild(greenHealthbarPlayer);
	// Create the world
	contactListener = new ContactListener();
	world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);
	// Create the textfile for loading files
	LoadingErrors = "";
	textfile = new Textfile();
}

Level::~Level()
{
	// Delete the allocated memory
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
	std::vector<Text*>::iterator itText = textVector.begin();
	while (itText != textVector.end()) {
		delete (*itText);
		itText = textVector.erase(itText);
	}

	delete world;
	delete contactListener;
}

void Level::Update(double deltaTime)
{
	// Check if the player contacted the finish
	if (finish->Contact(player)) {
		finished = true;
	}
	// Update the world
	world->Step(deltaTime, 8, 3);
	// Update the healthbar
	greenHealthbarPlayer->SetWidth(player->GetCurrentHealth()/player->GetMaxHealth() * 700);

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

void Level::LoadFile(std::string filename)
{
	// Try to open the file
	if (textfile->Open(filename.c_str())) {
		// Start reading the filee
		textfile->StartReading();
		while (!textfile->EndOfFile()) {
			std::string lineoftext = textfile->ReadLine();
			ReadLine(lineoftext);
		}
		// Close the file and initialize the level
		textfile->Close();
		Init();
	}
	else {
		// file could not be opened so throw a erorr
		LoadingErrors = "Could not find: " + filename;
	}
}

void Level::Init()
{
	// Set the the player and intiialize the enemies
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->SetPlayer(player);
		enemies[i]->UpdateChilderen(this, 0);
		enemies[i]->Init();
	}
	// Links the doors with the crystals
	for (int i = 0; i < tmpLinks.size(); i++) {
		for (int j = 0; j < tmpLinks[i].crystalIDs.size(); j++) {
			for (int k = 0; k < tmpCrystals.size(); k++) {
				if (tmpLinks[i].crystalIDs[j] == tmpCrystals[k]->GetUniqueID()) {
					tmpLinks[i].door->Link(tmpCrystals[k]);
				}
			}
		}
	}
	// Clear all the the tmp link data
	tmpLinks.clear();
	tmpCrystals.clear();
	this->UpdateChilderen(this, 0);
	world->SetContactListener(contactListener);
}

void Level::ReadLine(std::string line)
{
	// FLOOR
	if (line[0] == 'f' && line[1] == 'l') {
		glm::vec2 _pos;
		float _angle;
		int _width;
		int _height;
		sscanf(line.c_str(), "floor %f %f %f %d %d", &_pos.x, &_pos.y, &_angle, &_width, &_height);
		Sprite* _floor = new Sprite(_width, _height, ResourceManager::GetTexture("floor")->GetId());
		_floor->localPosition = _pos;
		_floor->localAngle = _angle;
		_floor->SetUV(glm::vec4(0, 0, _floor->GetWidth() / 200.0f, _floor->GetHeight() / 200.0f));
		AddChild(_floor);
		levelObjects.push_back(_floor);
	}
	// WALL
	else if (line[0] == 'w') {
		glm::vec2 _pos;
		float _angle;
		float _width;
		sscanf(line.c_str(), "wall %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width);
		B2Entity* _wall = new B2Entity(_width, 750, ResourceManager::GetTexture("wall")->GetId(), world);
		_wall->CreateBoxCollider(_width, 100, glm::vec2(0.0f, 0.0f), false, false);
		_wall->localPosition = _pos;
		_wall->localAngle = _angle;
		_wall->SetUV(glm::vec4(0, 0, _wall->GetWidth() / 720.0f, _wall->GetHeight() / 750.0f));
		AddChild(_wall);
		levelObjects.push_back(_wall);
	}
	// MIRROR
	else if (line[0] == 'm') {
		glm::vec2 _pos;
		float _angle;
		int _rotatable;
		sscanf(line.c_str(), "mirror %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_rotatable);
		Mirror* _mirror = new Mirror(_rotatable, 150.0f, 150.0f, ResourceManager::GetTexture("mirror")->GetId(), world);
		_mirror->CreateBoxCollider(100.0f, 110.0f, glm::vec2(0.15f, 0.0f), false, false);
		_mirror->localPosition = _pos;
		_mirror->SetRotation(glm::degrees(_angle));
		_mirror->localAngle = _angle;

		AddChild(_mirror);
		levelObjects.push_back(_mirror);
	}
	// CRYSTAL
	else if (line[0] == 'c') {
		glm::vec2 _pos;
		float _angle;
		float uniqueID;
		glm::vec4 color = glm:: vec4(0, 0, 0, 1);
		sscanf(line.c_str(), "crystal %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &uniqueID, &color.r, &color.g, &color.b);
		Crystal* _crystal = new Crystal(uniqueID, 70, 70, ResourceManager::GetTexture("crystal")->GetId(), world);
		_crystal->CreateBoxCollider(70, 70, glm::vec2(0.0f, 0.0f), false, false);
		_crystal->localPosition = _pos;
		_crystal->localAngle = _angle;
		_crystal->SetColor(color);
		AddChild(_crystal);
		levelObjects.push_back(_crystal);
		tmpCrystals.push_back(_crystal);
	}
	// DOOR
	else if (line[0] == 'd') {
		glm::vec2 _pos;
		float _angle;
		float _crystals;
		glm::vec4 color = glm::vec4(0, 0, 0, 1);
		sscanf(line.c_str(), "door %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &color.r, &color.g, &color.b, &_crystals);
		Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
		_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
		_door->localPosition = _pos;
		_door->localAngle = _angle;
		_door->SetColor(color);
		AddChild(_door);
		levelObjects.push_back(_door);
		Link link;
		link.door = _door;
		for (int i = 0; i < _crystals; i++) {
			line = textfile->ReadLine();
			int _crystalid;
			sscanf(line.c_str(), "%d", &_crystalid);
			link.crystalIDs.push_back(_crystalid);
		}
		tmpLinks.push_back(link);
	}
	// ENEMY
	else if (line[0] == 'e') {
		glm::vec2 _pos;
		float _angle;
		float _health;
		float _damage;
		float _speed;
		float _LOS;//LOS short for LineOfSight
		sscanf(line.c_str(), "enemy %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_speed, &_damage, &_LOS);
		Enemy* _enemy = new Enemy(NULL, _LOS, 0.6f, 0.5f, _health, _speed, _damage, 70, 70, ResourceManager::GetTexture("enemy")->GetId(), world);
		_enemy->CreateBoxCollider(70, 70, glm::vec2(0, 0), true, false);
		_enemy->localPosition = _pos;
		_enemy->localAngle = _angle;
		AddChild(_enemy);
		enemies.push_back(_enemy);
	}
	// PLAYER
	else if (line[0] == 'p') {
		glm::vec2 _pos;
		float _angle;
		float _health;
		float _damage;
		float _speed;
		sscanf(line.c_str(), "player %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_health, &_damage, &_speed);
		player = new Player(camera, _health, _speed, _damage, 100, 100, ResourceManager::GetTexture("player")->GetId(), world);
		player->CreateCircleCollider(40.0f, true, false);
		player->localPosition = _pos;
		player->localAngle = _angle;
		//player->Update(0);
		player->UpdateChilderen(this, 0);
		AddChild(player);
	}
	// FINISH
	else if (line[0] == 'f' && line[1] == 'i') {
		glm::vec2 _pos;
		float _angle;
		float _width;
		float _height;
		sscanf(line.c_str(), "finish %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width, &_height);
		finish = new B2Entity(_width, _height, 0, world);
		finish->CreateBoxCollider(_width, _height, glm::vec2(0, 0), true, true);
		finish->localPosition = _pos;
		finish->localAngle = _angle;
		AddChild(finish);
	}
}

void Level::LoadTutorial()
{
	// All of the data of the tutorial level
	std::string tutorialString[] {
		"floor -52.000000 910.000000 0.000000 550 4000",
		"floor -78.134888 3714.808594 0.000000 3300 2100",
		"floor -63.607788 5809.004395 0.000000 550 2100",
		"wall -50.000000 -1040.000000 0.000000 720",
		"wall 263.594482 803.651245 1.570796 3600",
		"wall -364.405518 807.651245 1.570796 3600",
		"door -51.730713 2646.793701 0.000000 1.000000 0.000000 0.000000 1",
		"1",
		"crystal -193.730713 2422.793701 0.000000 1 1.000000 0.000000 0.000000",
		"wall 940.294189 2654.337158 0.000000 1440",
		"wall -1047.705811 2652.337158 0.000000 1440",
		"wall -1729.132202 3680.050781 1.570796 2160",
		"wall 1612.586426 3681.895508 1.570796 2160",
		"wall -1065.898682 4714.273926 0.000000 1440",
		"wall 941.484619 4714.927734 0.000000 1440",
		"door -65.148315 4708.441895 0.000000 0.000000 1.000000 0.000000 2",
		"5",
		"4",
		"wall -1064.328125 3711.977539 0.000000 1440",
		"crystal -784.328125 3319.977539 0.000000 4 0.000000 1.000000 0.000000",
		"crystal -788.328125 4099.977539 0.000000 5 0.000000 1.000000 0.000000",
		"mirror 71.671875 3705.977539 4.3 1",
		"wall 261.416016 5478.670410 1.570796 1440",
		"wall -390.583984 5472.670410 1.570796 1440",
		"wall 261.787109 6909.774414 1.570796 1440",
		"wall -388.213013 6905.774414 1.570796 1440",
		"enemy -81.718872 5139.854492 4.712389 300.000000 7.000000 150.000000 3000.000000",
		"player -38.000000 -588.000000 4.712389 600.000000 100.000000 10.000000",
		"finish -67.864746 5764.488281 0.000000 500 100"
	};
	// There are 29 lines for the tutorials
	for (int i = 0; i < 29; i++) {
		// Load the door in a custom way because in the ReadLine function it makes use of the TextFile and this is a string
		if (tutorialString[i][0] == 'd') {
			glm::vec2 _pos;
			float _angle;
			float _crystals;
			glm::vec4 color = glm::vec4(0, 0, 0, 1);
			sscanf(tutorialString[i].c_str(), "door %f %f %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &color.r, &color.g, &color.b, &_crystals);
			Door* _door = new Door(550, 550, ResourceManager::GetTexture("door")->GetId(), world);
			_door->CreateBoxCollider(550, 100, glm::vec2(0, 0), false, false);
			_door->localPosition = _pos;
			_door->localAngle = _angle;
			_door->SetColor(color);
			AddChild(_door);
			levelObjects.push_back(_door);
			Link link;
			link.door = _door;
			for (int j = 0; j < _crystals; j++) {
				i++;
				int _crystalid;
				sscanf(tutorialString[i].c_str(), "%d", &_crystalid);
				link.crystalIDs.push_back(_crystalid);
			}
			tmpLinks.push_back(link);
		}
		ReadLine(tutorialString[i]);
	}
	// Init the tutorial
	Init();
	// Place the text for the tutorial
	Text* text = new Text("Move the player with w-a-s-d or the arrow keys", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 300;
	text->localPosition.y = -750;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("Rotate the player using the mouse", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 300;
	text->localPosition.y = 750;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("Aim your mouse at the crystal and shoot your laser", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 300;
	text->localPosition.y = 2500;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("by holding left mouse button to open the door", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 300;
	text->localPosition.y = 2440;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("Try hitting both of the crystals using the mirror", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 200;
	text->localPosition.y = 3750;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("but be careful a enemy awaits you on the other side of the door", ResourceManager::GetFont("fonts/arial.ttf", 512, 48), glm::vec3(1, 1, 1), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 200;
	text->localPosition.y = 3690;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
	text = new Text("Also note that the mirror can be rotated by pushing it", ResourceManager::GetFont("fonts/arial.ttf", 1024, 60), glm::vec3(1, 0, 0), Text::AlignmentX::leftX, Text::AlignmentY::bottomY);
	text->localPosition.x = 200;
	text->localPosition.y = 3615;
	text->SetTextRenderer(RenderManager::GetTextRenderer("freetypeworld"));
	AddChild(text);
	textVector.push_back(text);
}