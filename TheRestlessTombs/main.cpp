#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "resourceManager.h"
#include "scene.h"
#include "camera.h"
#include "text.h"
#include "player.h"
#include "level1.h"
#include "window.h"
#include "contactListener.h"
#include "button.h"
#include "menu.h"
#include "playerHud.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

Window* window;

Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;
ContactListener* contactListener;

PlayerHud* playerHud;
Player* player;
Shop* shop;
Level1* level1;
float Window::m2p = 50;
float Window::p2m = 1 / Window::m2p;

GameState gameState;
Menu* menu;
bool initMenu;

int main() {
	window = new Window(800, 600, "TheRestlessTombs", true);
	window->SetBackgroundColor(glm::vec3(0.258823529f, 0.156862745f, 0.207843137f));
	camera = window->GetCamera();
	input = window->GetInput();
	rm = window->GetResourceManager();

	// Load shaders
	rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	rm->CreateShader("debugRenderer", "shaders//debugRenderer.vs", "shaders//debugRenderer.fs");
	rm->CreateShader("hud", "shaders//hud.vs", "shaders//hud.fs");
	rm->CreateShader("text", "shaders//text.vs", "shaders//text.fs");
	rm->CreateShader("textHud", "shaders//textHUD.vs", "shaders//textHUD.fs");
	rm->CreateShader("color", "shaders//color.vs", "shaders//color.fs");
	rm->CreateShader("colorHUD", "shaders//colorHUD.vs", "shaders//colorHUD.fs");
	rm->CreateShader("bomb", "shaders//bomb.vs", "shaders//bomb.fs");
	rm->CreateShader("healthbar", "shaders//healthbar.vs", "shaders//healthbar.fs");
	rm->CreateShader("person", "shaders//person.vs", "shaders//person.fs");

	// Load textures
	rm->CreateTexture("player", "textures/Player.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("wall", "textures/Wallx3.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("secretWall", "textures/SecretWall.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("floor", "textures/FloorStandard.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("floorDetailed", "textures/Floor2.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("stairs", "textures/Stairs.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorNorth", "textures/DoorNorth.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorEast", "textures/DoorEast.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorSouth", "textures/DoorSouth.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorWest", "textures/DoorWest.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("playerSword", "textures/PlayerSword.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("crate", "textures/Crate.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doubleCrate", "textures/DoubleCrate.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("healthPotion", "textures/HealthPotion.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("speedPotion", "textures/SpeedPotion.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("damagePotion", "textures/DamagePotion.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("showCase", "textures/ShowCase.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("goldLootChestClosed", "textures/GoldLootChestClosed.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("goldLootChestOpened", "textures/GoldLootChestOpened.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("silverLootChestClosed", "textures/SilverLootChestClosed.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("silverLootChestOpened", "textures/SilverLootChestOpened.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("heartEmpty", "textures/HeartEmpty.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("heartFilled", "textures/HeartFilled.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("orcWeapon", "textures/OrcWeapon.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("babyOrc", "textures/BabyOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("psychoOrc", "textures/PsyhcoOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("psychoOrcWeapon", "textures/PsyhcoOrcWeapon.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("orc", "textures/Orc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("armoredOrc", "textures/ArmoredOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("necromancerOrc", "textures/NecromancerOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("bomb", "textures/Bomb.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("bomberOrc", "textures/BomberOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("bossOrc", "textures/BossOrc.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("bossOrcWeapon", "textures/BossOrcWeapon.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("gold", "textures/Gold.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("explosion", "textures/Explosion.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("shop", "textures/Shopkeeper.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);

	// Create the world, player, shop and level
	world = new b2World(b2Vec2(0.0f, 0.0f));
	playerHud = new PlayerHud(rm, camera);
	player = new Player(playerHud, input, rm, camera, rm->GetShader("person"), world);
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(0, 0, 50, 75, true, false);
	shop = new Shop(player, rm, input, camera, rm->GetShader("shader"), world);
	shop->GiveTexture(rm->GetTexture("shop"));
	shop->CreateBody(0, 0, 70 , 70, false, false);
	level1 = new Level1(player, shop, world, rm, input, camera);
	level1->Update(window->GetDeltaTime());
	// Set the contactListener after all of the bodies are intialized and in place
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);
	gameState = GameState::_menu;
	menu = new Menu(rm, input, camera);
	initMenu = false;


	// THE GAME LOOP
	while (!input->Quit() && !menu->Quit()) {
		// Clear the window and update the window
		window->ClearWindow();
		window->Update();

		switch (gameState) {
		case _game:
			/*if (input->KeyPress(SDL_SCANCODE_1)) {
				gameState = GameState::_shop;
				shop->_SetActive(true);
			}*/
			// Check if the shop is active, if so switch to that state instead
			if (shop->IsActive()) {
				gameState = GameState::_shop;
				window->SetBackgroundColor(glm::vec3(0.258823529f, 0.156862745f, 0.207843137f));
				continue;
			}
			// Update level1
			level1->Update(window->GetDeltaTime());
			// Update the box2d world
			world->Step(window->GetDeltaTime(), 8, 3);
			// Press escape to switch to the menu
			if (input->KeyPress(SDL_SCANCODE_ESCAPE)) {
				gameState =  GameState::_menu;
				menu->SetActive(true);
				window->SetBackgroundColor(glm::vec3(0.258823529f, 0.156862745f, 0.207843137f));
				if (!initMenu) {
					menu->InitMenu();
					initMenu = true;
				}
			}
			break;

		case _menu:
			// Update the menu
			menu->Update(window->GetDeltaTime());
			if (!menu->IsActive()) {
				gameState =  GameState::_game;
				window->SetBackgroundColor(glm::vec3(0.0f, 0.0f, 0.0f));
			}
			// If the restart button is pressed restart the game and launch the game
			if (menu->Restart()) {
				level1->Reset();
				gameState =  GameState::_game;
				window->SetBackgroundColor(glm::vec3(0.0f, 0.0f, 0.0f));
			}
			break;

		case _shop:
			// Update and draw shop
			shop->Update(window->GetDeltaTime());
			shop->Draw();
			if (!shop->IsActive()) {
				gameState = GameState::_game;
				window->SetBackgroundColor(glm::vec3(0.0f, 0.0f, 0.0f));
			}
			// If escape is pressed go to the menu
			else if (input->KeyPress(SDL_SCANCODE_ESCAPE)) {
				gameState =  GameState::_menu;
				menu->SetActive(true);
				window->SetBackgroundColor(glm::vec3(0.258823529f, 0.156862745f, 0.207843137f));
				if (!initMenu) {
					menu->InitMenu();
					initMenu = true;
				}
			}
			break;
		}

		// Update window with OpenGL rendering
		window->SwapBuffers();
	}// THE END OF THE GAME LOOP

    // DELETE ALL VARIABLES CREATED WITH THE KEYWORD "new"
	delete window;
    delete level1;
    delete playerHud;
    delete player;
    delete shop;
    delete contactListener;
    delete world;

    delete menu;

    // end of the program
    std::cout << "Program succeeded" << std::endl;
	return 0;
}
