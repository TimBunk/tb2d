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
#include "tickbox.h"
#include "textinput.h"

class LevelEditor : public Scene
{
public:
	LevelEditor(int screenWidthCamera, int screenHeightCamera);
	~LevelEditor();

	void Update(double deltaTime);
	bool UpdateTickboxes();

	Level* GetCurrentLevel();
	void StopCurrentLevel();

	void Save(char* levelname);

	Entity* GetPlaceable();
	void DeleteCurrentlySeleceted();

	void CreatePlaceablesTickbox(std::string text, glm::vec2 position);
	void CreateEditorModeTickbox(std::string text, glm::vec2 position);

private:
	Sprite* canvasEditor;

	std::vector<B2Entity*> walls;
	int wallWidth, wallHeight, wallRotation;

	enum Placeables
	{
		player,
		wall,
		mirror,
		crystal,
		floor,
		door,
		finish
	};
	Placeables currentPlaceable;
	std::vector<Tickbox*> tickboxes;
	std::vector<Text*> tickboxesText;

	enum EditorMode
	{
		select,
		place
	};
	EditorMode mode;
	std::vector<Tickbox*> tickboxesMode;
	std::vector<Text*> tickboxesModeText;

	Textinput* inputtest;

	Textfile* textfile;
	Loadlevel* levelLoader;
	Level* level;

	b2World* world;
	Entity* currentlySelected;

	Button* saveButton;
	Button* loadButton;
	Button* menuButton;
};

#endif // !LEVELEDITOR_H
