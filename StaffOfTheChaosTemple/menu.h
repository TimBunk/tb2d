#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "resourceManager.h"
#include "input.h"
#include "text.h"
#include "button.h"

class Menu : public Scene {
public:
	Menu(int screenWidthCamera, int screenHeightCamera);
	~Menu();

	void Update(double deltaTime);

	bool Start();
	bool Editor();
	bool Quit();

private:
	Sprite* background;
	Text* creditsProgrammer;
	Text* creditsArtist;
	bool start; 
	bool editor;
	bool quit; 
	Button* startButton;
	Button* editorButton;
	Button* quitButton;
};

#endif //! MENU_H
