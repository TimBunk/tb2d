/**
 * @file menu.h
 *
 * @brief The menu header file.
 */

#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "resourceManager.h"
#include "input.h"
#include "text.h"
#include "button.h"

/**
 * @brief The menu class
 */
class Menu : public Scene {
public:
	/// @brief Constructor of the Menu class
	/// @param rm The resourceManager is needed for creating the buttons
	/// @param input The input class is needed because the menu uses the escape key to exit the menu
	/// @param camera The reason it takes a camera is for drawing the object with the view and projection matrix that can be received from the camera
	Menu(int screenWidthCamera, int screenHeightCamera);

	/// @brief Destructor of the Menu
	virtual ~Menu();

	/// @brief Update update function keeps track of buttons that are pressed or hovered over
	/// @param deltaTime is the time in seconds between 2 frames you can find the deltaTime in the @file window.h class by calling the function GetDeltaTime()
	/// @return void
	void Update(double deltaTime);

	/// @brief IsActive returns the active boolean of the Menu
	///@return bool
	bool Start();
	bool Editor();

	/// @brief returns a boolean that will be true whenever the quit button is pressed
	bool Quit();
private:
	Sprite* background;
	Text* creditsProgrammer;
	Text* creditsArtist;
	bool start; ///< @brief active Represents current state of the menu
	bool editor;
	bool quit; ///< @brief quit Is a boolean that will be true when the quit button is pressed
	Button* startButton; ///< @brief startButton Is the a button that can be pressed for when you want to start the game
	Button* editorButton;
	Button* quitButton; ///< @brief quitButton Is a button that can be pressed for when you want to quit the game
};

#endif //! MENU_H
