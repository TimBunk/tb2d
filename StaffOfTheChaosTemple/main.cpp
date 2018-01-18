#include <iostream>
#include <string>

#include <gl\glew.h>
#include <glfw3.h>
#include <glm-0.9.8.4\glm\glm.hpp>
#include <glm-0.9.8.4\glm\gtc\matrix_transform.hpp>
#include <glm-0.9.8.4\glm\gtc\type_ptr.hpp>
#include <glm-0.9.8.4\glm\gtx\matrix_decompose.hpp>

#include "window.h"
#include "box2Dclasses/contactListener.h"
#include "sprite.h"
#include "scene.h"
#include "menu.h"
#include "button.h"
#include "box2Dclasses/b2entity.h"
#include "player.h"
#include "level1.h"
#include "level2.h"
#include "mirror.h"
#include "rotator.h"
#include "crystal.h"
#include "door.h"
#include "core.h"
#include "leveleditor.h"
#include "textrenderer.h"
#include "levelselector.h"

Core* core;
Menu* menu;
Levelselector* levelSelector;
LevelEditor* levelEditor;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

enum GameState
{
	_selector,
	_game,
	_editor,
	_menu
};

GameState gameState;

int main() {
	core = new Core("Staff of the Chaos Temple", false);
	core->ResizeWindow(1600, 900);
	//core->ResizeWindow(800, 600);
	core->SetWindowBackgroundColor(glm::vec3(0.0f, 0.4f, 0.8f));

	ResourceManager::CreateTexture("awesome", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("player", "textures/player.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("wall", "textures/wall.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("staff", "textures/staff.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("laser", "textures/laser.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("crystal", "textures/crystal.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("enemy", "textures/enemy.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("sword", "textures/weapon_enemy.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("door", "textures/door.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("mirror", "textures/mirror.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("rotator", "textures/rotator2.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("floor", "textures/floor_tiles.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("laserParticle", "textures/laserParticle.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("tickboxNotActive", "textures/tickbox.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("tickboxActive", "textures/tickboxactive.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("textinput", "textures/textinput.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("menu", "textures/menu.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);

	ResourceManager::CreateShader("laser", "shaders\\basic.vs", "shaders\\laserParticle.fs");
	RenderManager::CreateParticleRenderer(1, "particle", ResourceManager::GetShader("laser"));
	RenderManager::CreateTextRenderer(0, "freetypeworld", ResourceManager::GetShader("freetype"), false);

	gameState = _menu;
	menu = new Menu(1920, 1080);
	levelSelector = new Levelselector(1920, 1080);
	levelEditor = new LevelEditor(3840, 2160);

	while (core->IsWindowActive()) {
		switch (gameState)
		{
		case _selector:
			// Run the selector
			core->Run(levelSelector);
			// If a level has been loaded switch to the gamestate _game
			if (levelSelector->GetLevel() != nullptr) {
				gameState = _game;
			}
			// If escape has been pressed return to menu
			if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
				gameState = _menu;
			}
			break;
		case _game:
			// Run the level
			core->Run(levelSelector->GetLevel());
			// If the player finished inform the levelselctor about it and switch game state
			if (levelSelector->GetLevel()->IsFinished()) {
				levelSelector->FinishLevel();
				gameState = _selector;
			}
			// If the player died inform the levelselector about it and switch game state
			else if (levelSelector->GetLevel()->IsPlayerAlive() == false) {
				levelSelector->EndLevel();
				gameState = _selector;
			}
			else if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
				levelSelector->ExitLevel();
				gameState = _selector;
			}
			break;
		case _editor:
			core->Run(levelEditor);
			// If the escape key is pressed or the menu button switch the game state to menu
			if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
				gameState = _menu;
			}
			break;
		case _menu:
			core->Run(menu);
			// If start is pressed open the _selector
			if (menu->Start()) {
				DebugRenderer::SetActive(false);
				gameState = _selector;
			}
			// If editor is pressed open the editor
			else if (menu->Editor()) {
				DebugRenderer::SetActive(true);
				gameState = _editor;
			}
			// If quit is pressed exit the application
			else if (menu->Quit()) {
				core->CloseWindow();
			}
			break;
		}
	}
	// Delete the scenes and the core
	delete menu;
	delete levelSelector;
	delete levelEditor;
	delete core;
	// Program succeeded!
	std::cout << "Program succeeded" << std::endl;
	return 0;
}