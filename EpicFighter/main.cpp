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
#include "window.h"
#include "box.h"
#include "player.h"
#include "ground.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

bool quit;

Window* window;

Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;

Player* player1;
Ground* ground;

float Window::m2p = 50;
float Window::p2m = 1 / Window::m2p;

int main() {
	quit = false;
	window = new Window(800, 600, "TheRestlessTombs", false);
	camera = window->GetCamera();
	input = window->GetInput();
	rm = window->GetResourceManager();
	rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	rm->CreateTexture("player", "textures/Player.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("playerHand", "textures/PlayerHand.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("wall", "textures/Wallx3.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("floorStandard", "textures/FloorStandard.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("floorDetailed", "textures/Floor2.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("stairs", "textures/Stairs.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorNorth", "textures/DoorNorth.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorEast", "textures/DoorEast.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorSouth", "textures/DoorSouth.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("doorWest", "textures/DoorWest.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("playerSword", "textures/PlayerSword.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("crate", "textures/Crate.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	world = new b2World(b2Vec2(0.0f, 9.91f));
	player1 = new Player(400, 300, 50, 75, true, world, camera, rm->GetShader("shader"));
	player1->SetTexture(rm->GetTexture("player"));
	player1->SetMovement(SDL_SCANCODE_A, SDL_SCANCODE_D, window->GetInput());
	ground = new Ground(camera->screenWidth/2, camera->screenHeight, camera->screenWidth, 200, false, world, camera, rm->GetShader("shader"));
	ground->SetTexture(rm->GetTexture("floorStandard"));
	// THE GAME LOOP
	while (!input->Quit()) {
		// Clear the window and update the window
		window->ClearWindow();
		window->Update();

		player1->Draw();
		player1->Update(window->GetDeltaTime());

		ground->Draw();

		// Update the box2d world
		world->Step(window->GetDeltaTime(), 8, 3);
		// Update window with OpenGL rendering
		window->SwapBuffers();
	}// THE END OF THE GAME LOOP

    // DELETE ALL VARIABLES CREATED WITH THE KEYWORD "new"
	delete window;
    delete world;

    std::cout << "Program succeeded" << std::endl;
	return 0;
}
