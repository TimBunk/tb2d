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

	Level* GetLevel();
	void FinishLevel();
	void EndLevel();
	void ExitLevel();

private:
	void LoadLevel(std::string filename);

	Level* level;
	Text* nameReceiverText;
	Textinput* nameReceiver;
	Button* load;

	Button* victoryDefeat;
	Button* error;
};

#endif // !LEVELSELECTOR_H
