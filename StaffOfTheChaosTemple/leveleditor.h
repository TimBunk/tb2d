#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <fstream>
#include <cstring>
#include <iomanip>

#include "scene.h"
#include "box2Dclasses/b2entity.h"
#include "button.h"
#include "box2Dclasses/contactListener.h"
#include "textfile.h"
#include "loadlevel.h"
#include "tickbox.h"
#include "textinput.h"
#include "player.h"

struct InputFloat {
	Text* text = nullptr;
	Textinput* input = nullptr;
	float output = 0.0f;
};

class LevelEditor : public Scene
{
public:
	LevelEditor(int screenWidthCamera, int screenHeightCamera);
	~LevelEditor();

	void Update(double deltaTime);
	void UpdateSelectMode();
	void UpdatePlaceMode();

	void UpdateTickboxes();
	void UpdateInputFloats();

	void Place();
	void Select();

	void GetPlaceable();
	void UpdateCurrentlySelected();
	void DeleteCurrentlySeleceted();

	void CreatePlaceablesTickbox(std::string text, glm::vec2 position);
	void CreateEditorModeTickbox(std::string text, glm::vec2 position);
	InputFloat CreateInputFloat(Sprite* canvas, std::string startValue, glm::vec2 position, std::string text);
	Sprite* CreateCanvasPlaceable(std::string name);

	Level* GetCurrentLevel();
	void StopCurrentLevel();

	void Save(char* levelname);

private:
	enum Placeables
	{
		player,
		wall,
		mirror,
		crystal,
		floor,
		door,
		enemy,
		finish
	};
	struct EditorObject {
		Entity* entity = nullptr;
		Placeables type;
	};
	std::vector<EditorObject> editorObjects;
	Sprite* canvasEditor;
	Text* properties;

	Entity* canvasObjects;

	std::vector<Sprite*> propertiesCanvas;
	std::vector<InputFloat*> inputFloats;

	// Player canvas
	Sprite* playerCanvas;
	InputFloat inputPlayerRotation;
	InputFloat inputPlayerHealth;
	InputFloat inputPlayerDamage;
	InputFloat inputPlayerSpeed;
	Player* _player;
	// Wall canvas
	Sprite* wallCanvas;
	InputFloat inputWallWidth;
	InputFloat inputWallRotation;
	// Mirror canvas
	Sprite* mirrorCanvas;
	InputFloat inputMirrorRotation;
	// Crystal canvas
	Sprite* crystalCanvas;
	InputFloat inputCrystalRotation;
	// Floor canvas
	Sprite* floorCanvas;
	InputFloat inputFloorWidth;
	// Door canvas
	Sprite* doorCanvas;
	InputFloat inputDoorRotation;
	// Enemy canvas
	Sprite* enemyCanvas;
	InputFloat inputEnemyRotation;
	// Finish canvas
	Sprite* finishCanvas;
	InputFloat inputFinishWidth;
	InputFloat inputFinishHeight;
	Entity* _finish;

	std::vector<Text*> textVector;

	Placeables currentPlaceable;
	std::vector<Tickbox*> tickboxes;
	//std::vector<Text*> tickboxesText;

	enum EditorMode
	{
		select,
		place,
		move
	};
	EditorMode mode;
	std::vector<Tickbox*> tickboxesMode;
	//std::vector<Text*> tickboxesModeText;

	Textfile* textfile;
	Loadlevel* levelLoader;
	Level* level;

	b2World* world;
	EditorObject currentlySelected;

	Button* saveButton;
	Button* loadButton;
	Button* menuButton;
};

#endif // !LEVELEDITOR_H
