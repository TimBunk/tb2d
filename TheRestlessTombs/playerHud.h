/**
 * @file playerHud.h
 *
 * @brief The playerHud header file.
 */

#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include "scene.h"
#include "showCase.h"
#include "item.h"

/**
 * @brief The PlayerHud class
 */
class PlayerHud : public Scene {
public:
	/// @brief Constructor of the PlayerHud
	/// @param playerHud Is the hud the player will send information about himself to
	/// @param rm Is the resourceManager that is needed in order to create all of the hud objects
	/// @param camera Is the main camera that is needed in order to draw everything correctly
	PlayerHud(ResourceManager* rm, Camera* camera);

	/// @brief Destructor of the PlayerHud
	~PlayerHud();

	/// @brief this function takes care of setting the text of the stats
	/// @param text Is the text you want to display the stats
	/// @return void
	void UpdateStats(std::string text);

	/// @brief this function updates the textGold by the amount given
	/// @param amount Is the amount of gold you want to set as a text
	/// @return void
	void UpdateGold(int amount);

	/// @brief updateHealth updates the texture of the health to be filled or not
	/// @param currentHealth Is the amount of filled hearts you want to draw the others will not be filled
	/// @return voi
	void UpdateHealth(int currentHealth);

	/// @brief this function gives the showcase a item to display
	/// @param sci Is a ShowCaseItem struct that is needed in order to draw it with the showCase
	/// @return void
	void GiveShowcase(ShowCaseItem sci);

	/// @brief Checks if the showCase already contains a item
	/// @return bool
	bool IsShowCaseFull();

	/// @brief Clears all items out of the showCase
	/// @return void
	void ClearShowcase();

	/// @brief CreateLives will create new Hud elements that will represent the health of the player
	/// @param currentHealth Is the amount of lives that need to be filled the others will be be filled
	/// @param health Is the total amount of hearts
	/// @return void
	void CreateLives(int currentHealth, int health);

private:
	ResourceManager* rm; ///< @brief rm Is a resourceManager that is needed in order to create the hud objects
	ShowCase* showCase; ///< @brief showCase can visualize the item the player is holding
	Text* textGold; ///< @brief textGold is a text that displays the amount of gold you have
	Text* textStats; ///< @brief textStats is a text that display the values of all the player's stats
	std::vector<Hud*> hudHealth; ///< @brief hudHealth is a list with Hud's that represent the health of the player
};

#endif //! PLAYERHUD_H
