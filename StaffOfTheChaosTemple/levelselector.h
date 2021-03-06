#ifndef LEVELSELECTOR_H
#define LEVELSELECTOR_H

#include "scene.h"
#include "level.h"
#include "textinput.h"
#include "button.h"

class Levelselector : public Scene
{
public:
	Levelselector(int screenWidthCamera, int screenHeightCamera);
	~Levelselector();

	void Update(double deltaTime);

	Level* GetLevel() { return level; }
	void FinishLevel();
	void EndLevel();
	void ExitLevel();

private:
	void LoadLevel(std::string filename);
	void CreateLevelButton(std::string name, std::string level, glm::vec2 position);

	Level* level;
	Button* tutorial;

	Text* nameReceiverText;
	Textinput* nameReceiver;
	Button* load;

	Button* victoryDefeat;
	Button* error;

	std::vector<Button*> buttons;
	std::vector<std::string> levelname;
};

#endif // !LEVELSELECTOR_H
