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

#include <ft2build.h>
#include FT_FREETYPE_H

Core* core;
Level1* level1;
Level2* level2;
Menu* menu;
LevelEditor* levelEditor;
Text* sampletext;

float B2Entity::m2p = 50.0f;
float B2Entity::p2m = 1.0f / B2Entity::m2p;

enum GameState
{
	_game,
	_editor,
	_menu
};

GameState gameState;

int levelCounter = 0;
std::vector<Level*> levels;

int main() {
	std::cout << "hello world" << std::endl;
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
	ResourceManager::CreateTexture("enemy", "textures/TestEnemy.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("sword", "textures/TestEnemySword.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("door", "textures/door.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("mirror", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("rotator", "textures/container2.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::none);
	ResourceManager::CreateTexture("floor", "textures/floor_tiles.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("laserParticle", "textures/laserParticle.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("tickboxNotActive", "textures/tickbox.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);
	ResourceManager::CreateTexture("tickboxActive", "textures/tickboxactive.png", TextureWrap::repeat, TextureFilter::linear, MipmapFilter::linear_mipmap_linear);

	RenderManager::CreateParticleRenderer(1, "particle", ResourceManager::GetShader("default"));

	level1 = new Level1(1920, 1080);
	level2 = new Level2(1920, 1080);

	levels.push_back(level2);
	levels.push_back(level1);

	gameState = _menu;
	menu = new Menu(1920, 1080);

	levelEditor = new LevelEditor(1920, 1080);

	sampletext = new Text("the lazy dog jumps over the fence", ResourceManager::GetFont("fonts/arial.ttf", 1024, 96), glm::vec4(1, 1, 1, 0), Text::AlignmentX::centerX, Text::AlignmentY::centerY);
	//menu->AddChild(sampletext);

	while (core->IsActive()) {
		switch (gameState)
		{
		case _game:
			core->Run(levels[levelCounter]);
			if (levels[levelCounter]->IsFinished()) {
				levelCounter++;
				if (levelCounter == levels.size()) {
					levelCounter = 0;
				}
			}
			// if escaped is pressed go back in to the menu
			if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
				gameState = _menu;
			}
			break;
		case _editor:
			if (levelEditor->GetCurrentLevel() != nullptr) {
				core->Run(levelEditor->GetCurrentLevel());
				if (Input::KeyDown(GLFW_KEY_ESCAPE)) {
					levelEditor->StopCurrentLevel();
				}
			}
			else {
				core->Run(levelEditor);
				if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
					gameState = _menu;
				}
			}
			// if escaped is pressed go back in to the menu
			if (Input::KeyPress(GLFW_KEY_ESCAPE)) {
				gameState = _menu;
			}
			break;
		case _menu:
			core->Run(menu);
			// If start is pressed start the game
			if (menu->Start()) {
				gameState = _game;
			}
			else if (menu->Editor()) {
				gameState = _editor;
			}
			else if (menu->Restart()) {
				// TODO: restart level
			}
			else if (menu->Quit()) {
				// exit the application
				core->Close();
			}
			break;
		}
	}
	delete menu;
	delete level1;
	delete level2;
	delete levelEditor;
	delete sampletext;
	delete core;
	std::cout << "Program succeeded" << std::endl;
	return 0;
}