#define GLEW_STATIC
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

#include <GL/glew.h>
#include <SDL2/SDL.h>

Window* window;

Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;
ContactListener* contactListener;

Player* player;
Level1* level1;
float Window::m2p = 50;
float Window::p2m = 1 / Window::m2p;

int main() {
	window = new Window(800, 600, "TheRestlessTombs", false);
	camera = window->GetCamera();
	input = window->GetInput();
	rm = window->GetResourceManager();

	// Load shaders
	rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	rm->CreateShader("debugRenderer", "shaders//debugRenderer.vs", "shaders//debugRenderer.fs");
	rm->CreateShader("hud", "shaders//hud.vs", "shaders//hud.fs");
	rm->CreateShader("text", "shaders//text.vs", "shaders//text.fs");
	rm->CreateShader("textHud", "shaders//textHUD.vs", "shaders//textHUD.fs");
	rm->CreateShader("bomb", "shaders//bomb.vs", "shaders//bomb.fs");
	rm->CreateShader("healthbar", "shaders//healthbar.vs", "shaders//healthbar.fs");

	// Load textures
	rm->CreateTexture("player", "textures/Player.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("playerHand", "textures/PlayerHand.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("wall", "textures/Wallx3.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
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


	// Create the world, player and level
	world = new b2World(b2Vec2(0.0f, 0.0f));
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);
	player = new Player(input, rm, camera, rm->GetShader("shader"), world);
	player->GiveTexture(rm->GetTexture("player"));
	player->CreateBody(0, 0, 50, 75, true, false);
	level1 = new Level1(player, world, rm, input, camera);


	// THE GAME LOOP
	while (!input->Quit()) {
		// Clear the window and update the window
		window->ClearWindow();
		window->Update();

		level1->Update(window->GetDeltaTime());

		// Update the box2d world
		world->Step(window->GetDeltaTime(), 8, 3);
		// Update window with OpenGL rendering
		window->SwapBuffers();
	}// THE END OF THE GAME LOOP

    // DELETE ALL VARIABLES CREATED WITH THE KEYWORD "new"
	delete window;
    delete level1;
    delete player;
    delete contactListener;
    delete world;

    // end of the program
    std::cout << "Program succeeded" << std::endl;
	return 0;
}
