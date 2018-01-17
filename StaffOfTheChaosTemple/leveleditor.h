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

private:
	// Enums
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
	enum EditorMode
	{
		select,
		place,
		move
	};
	// Structs
	struct EditorObject {
		Entity* entity = nullptr;
		Placeables type;
	};
	// Functions
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
	void AddTextToGuide(std::string text, int fontsize, glm::vec2 position);

	void Save();
	void Load();
	void ClearScene();
	void Linking();
	// Variables
	std::vector<EditorObject> editorObjects; // All of the objects that will be placed in the scene
	std::vector<B2Entity*> floors; // Floors will be saved seperatly from the editorobjects because we always want those to be at the bottom
	std::vector<Tickbox*> editorObjectsTickBoxes; // All of the tickboxes
	std::vector<Sprite*> propertiesCanvas; // Canvas that will show all of the properties of the current seleted placeable
	std::vector<InputFloat*> inputFloats; // The user can enter a input and will return a floor
	std::vector<Text*> textVector; // All of the text can be saved in this single vector
	
	Sprite* canvasEditor; // Canvas for the editor
	Entity* canvasObjects; // Canvas for all of the objects

	Placeables currentPlaceable; // the current object that the user wants to place
	std::vector<Tickbox*> tickboxesPlaceable; // All of the tickboxes for all of the different placeables will be saved here

	EditorMode mode; // The current editor mode
	std::vector<Tickbox*> tickboxesMode; // All of the tickboxes for all of the different editor modes

	// Textfile for saving and loading files
	Textfile* textfile;

	b2World* world; // b2World for the objects
	EditorObject currentlySelected; // The currently selected object

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
	Tickbox* inputDoorLink;
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

	Textinput* nameReceiver; // Namereceiver will receive names for loading and saving files
	Button* warning; // Warning will show warning when needed
	bool warningState;
	Text* nameReceiverText; // Text of the namereceiver
	Button* saveButton; // Button for saving
	bool saving;
	Button* loadButton; // Button for loading
	bool loading;
	Button* clearButton; // Button to remove all of the placed objects from the scene

	Button* remove; // Button to remove the currentlyselected

	std::vector<Crystal*> tmpCrystals; // tmp crystals for when loading a file

	int crystalID; // CrystalID is the id that will be given to a crystal when a crystal is created
	std::vector<Link> links; // All of the links between doors and crystals will be saved in this vector
	Text* linkingText; // Linking text will give info on how to link a door with a crystal
	bool linking;

	bool guide;
	Sprite* canvasGuide; // The guide for using the editor
};

#endif // !LEVELEDITOR_H
