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

#include <GL/glew.h>
#include <SDL2/SDL.h>

bool quit;

Window* window;

Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;

Level1* level1;
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
	world = new b2World(b2Vec2(0.0f, 0.0f));
	level1 = new Level1(world, rm, input, camera);
	//glViewport(0, 0, 700, 500);
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
    delete world;

    std::cout << "Program succeeded" << std::endl;
	return 0;
}
