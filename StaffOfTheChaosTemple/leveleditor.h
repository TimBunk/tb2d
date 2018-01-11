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

	void CreateInputFloat(InputFloat& inputFloat, Sprite* canvas, std::string startValue, glm::vec2 position, std::string text);
	Tickbox* CreateTickbox(Sprite* canvas, bool startValue, glm::vec2 position, std::string text);
	Sprite* CreateCanvasPlaceable(std::string name);

	Level* GetCurrentLevel();
	void StopCurrentLevel();

	void Save();
	void Load();
	void ClearScene();

	std::string recentFilename;

	//bool
	bool Menu();

private:
	bool menu;
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
	std::vector<B2Entity*> floors;
	std::vector<EditorObject> editorObjects;
	std::vector<Tickbox*> editorObjectsTickBoxes;
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
	Tickbox* inputMirrorRotator;
	// Crystal canvas
	Sprite* crystalCanvas;
	InputFloat inputCrystalRotation;
	// Floor canvas
	Sprite* floorCanvas;
	InputFloat inputFloorRotation;
	InputFloat inputFloorWidth;
	InputFloat inputFloorHeight;
	// Door canvas
	Sprite* doorCanvas;
	InputFloat inputDoorRotation;
	// Enemy canvas
	Sprite* enemyCanvas;
	InputFloat inputEnemyRotation;
	InputFloat inputEnemyHealth;
	InputFloat inputEnemyDamage;
	InputFloat inputEnemySpeed;
	InputFloat inputEnemyLOS;
	// Finish canvas
	Sprite* finishCanvas;
	InputFloat inputFinishRotation;
	InputFloat inputFinishWidth;
	InputFloat inputFinishHeight;
	B2Entity* _finish;

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

	Textinput* nameReceiver;
	Text* nameReceiverText;
	Button* saveButton;
	bool saving;
	bool saveWarningActive;
	Button* saveWarning;
	Button* loadButton;
	bool loading;
	Button* menuButton;
};

#endif // !LEVELEDITOR_H
