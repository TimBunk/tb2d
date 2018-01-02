#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <fstream>
#include <cstring>

#include "scene.h"
#include "box2Dclasses/b2entity.h"
#include "button.h"
#include "box2Dclasses/contactListener.h"
#include "textfile.h"
#include "loadlevel.h"

class LevelEditor : public Scene
{
public:
	LevelEditor(int screenWidthCamera, int screenHeightCamera);
	~LevelEditor();

	void Update(double deltaTime);

	Level* GetCurrentLevel();
	void StopCurrentLevel();

	void Save(char* levelname);

private:
	Textfile* textfile;
	Loadlevel* levelLoader;
	Level* level;

	b2World* world;
	Entity* currentlySeleceted;

	Button* saveButton;
	Button* loadButton;
	Button* wallButton;
	std::vector<B2Entity*> walls;
};

#endif // !LEVELEDITOR_H
