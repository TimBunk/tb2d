#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "b2entity.h"
#include "circle.h"
#include "text.h"
#include "window.h"
#include "contactListener.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

bool quit;

Window* window;
Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;
ContactListener* contactListener;

float Window::m2p = 50;
float Window::p2m = 1 / Window::m2p;

B2Entity* box1;
B2Entity* ground;
Circle* circle;
std::vector<B2Entity*> entities;

int main() {
	quit = false;
	window = new Window(1920, 1080, "Box2dLes", false);
	window->SetBackgroundColor(glm::vec3(0.5f, 0.5f, 0.5f));
	camera = window->GetCamera();
	input = window->GetInput();
	rm = window->GetResourceManager();
	rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	rm->CreateShader("debugRenderer", "shaders//debugRenderer.vs", "shaders//debugRenderer.fs");
	rm->CreateShader("textHud", "shaders//textHUD.vs", "shaders//textHUD.fs");

	rm->CreateTexture("crate", "textures/Crate.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("face", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	rm->CreateTexture("floor", "textures/FloorStandard.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
	world = new b2World(b2Vec2(0.0f, 9.81f));
	contactListener = new ContactListener();
	world->SetContactListener(contactListener);


	box1 = new B2Entity(camera, rm->GetShader("shader"));
	box1->GiveTexture(rm->GetTexture("crate"));
	box1->CreateBody(camera->screenWidth/2, camera->screenHeight/2, 250, 250, true, false, world);
	entities.push_back(box1);

	ground = new B2Entity(camera, rm->GetShader("shader"));
	ground->GiveTexture(rm->GetTexture("floor"));
	ground->CreateBody(camera->screenWidth/2, camera->screenHeight, camera->screenWidth, 300, false, false, world);
	entities.push_back(ground);

	circle = new Circle(camera, rm->GetShader("shader"), rm->GetShader("debugRenderer"));
	circle->GiveTexture(rm->GetTexture("face"));
	circle->CreateBody(500, 0,100, world);
	entities.push_back(circle);


	// THE GAME LOOP
	while (!input->Quit()) {
		// Clear the window and update the window
		window->ClearWindow();
		window->Update();

		for (int i=0;i<entities.size();i++) {
			entities[i]->Draw();
			entities[i]->Update(window->GetDeltaTime());
		}
		if (input->MousePress(1)) {
			Circle* circle2;
			circle2 = new Circle(camera, rm->GetShader("shader"), rm->GetShader("debugRenderer"));
			circle2->GiveTexture(rm->GetTexture("face"));
			circle2->CreateBody(input->GetMousePositionScreenSpace(camera).x, input->GetMousePositionScreenSpace(camera).y,20, world);
			entities.push_back(circle2);
		}

		// Update the box2d world
		world->Step(window->GetDeltaTime(), 8, 3);
		// Update window with OpenGL rendering
		window->SwapBuffers();
	}// THE END OF THE GAME LOOP

	// DELETE ALL VARIABLES CREATED WITH THE KEYWORD "new"
	while (entities.size() > 0) {
		int i = entities.size() - 1;
		delete entities[i];
		entities.pop_back();
	}
	delete window;
	delete contactListener;
    delete world;

    std::cout << "Program succeeded" << std::endl;
	return 0;
}
