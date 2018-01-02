#include "loadlevel.h"

Loadlevel::Loadlevel()
{
	textfile = new Textfile();
}

Loadlevel::~Loadlevel()
{
	delete textfile;
}

Level * Loadlevel::LoadFromFile(char* filename)
{
	if (textfile->Open(filename)) {
		Level* level = new Level(1920, 1080);
		textfile->StartReading();
		while (!textfile->EndOfFile()) {
			std::string lineoftext = textfile->ReadLine();
			if (lineoftext[0] == 'w') {
				std::cout << lineoftext << std::endl;
				glm::vec2 _pos;
				float _angle;
				float _width;
				sscanf(lineoftext.c_str(), "wall %f %f %f %f %f", &_pos.x, &_pos.y, &_angle, &_width);
				B2Entity* wall = new B2Entity(_width, 750, ResourceManager::GetTexture("wall")->GetId(), level->GetB2World());
				wall->CreateBoxCollider(_width, 100, glm::vec2(0.0f, 0.0f), false, false);
				wall->localPosition = _pos;
				wall->localAngle = _angle;
				level->AddChild(wall);
			}
		}
		level->CreateFinish(0, 540, 1920, 100);
		return level;
	}
	return nullptr;
}
