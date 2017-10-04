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
#include "configure.h"
#include "level1.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>


//const float screenWidth = 800, screenHeight = 600;
SDL_Window* window;
SDL_GLContext glContext;
bool quit;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float totalTime = 0.0f;
int fpsCount = 0;
void CalculateFrameRate();

Camera* camera;
Input* input;
ResourceManager* rm;
b2World* world;

Level1* level1;
float Configure::M2P = 50;
float Configure::P2M = 1 / Configure::M2P;
float Configure::screenWidth = 800.0f;
float Configure::screenHeight = 600.0f;

int main() {
	quit = false;
    window = nullptr;
    // Initialize SDL2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
    }
    else {
        window = SDL_CreateWindow("The Restless Tombs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Configure::screenWidth, Configure::screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (window == NULL) {
            std::cout << "sdl2 window creation failed! " << SDL_GetError() << std::endl;
        }
        else {
            glContext = SDL_GL_CreateContext(window);
            if (glContext == NULL) {
                std::cout << "failed to set glContext: " << SDL_GetError() << std::endl;
            }
            // set this to true so glew knows to use a modern approache to retrieving function pointers and extensions
            glewExperimental = GL_TRUE;

            // initialize glew
            if (GLEW_OK != glewInit()) {
                std::cout << "Error in initializing glew" << std::endl;
            }

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


            camera = new Camera(Configure::screenWidth, Configure::screenHeight);
			input = new Input();
			rm = new ResourceManager();
			rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
			rm->CreateTexture("player", "textures/Player.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
			rm->CreateTexture("wall", "textures/Wallx3.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
			world = new b2World(b2Vec2(0.0f, 0.0f));
			level1 = new Level1(world, rm, input, camera);

            // THE GAME LOOP
            while (!input->Quit()) {
                // Set background color
                glClearColor(0, 0.5, 0.5, 1);
                // Clear color buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                // Update the keyboard/mouse input
                input->Update();

                level1->Update();


                // Update the box2d world
                CalculateFrameRate();
                world->Step(deltaTime, 8, 3);
                // Update window with OpenGL rendering
                SDL_GL_SwapWindow(window);
            }// THE END OF THE GAME LOOP
        }
    }
    // CLEAR ALL ALLOCATED MEMORY IN SDL
    SDL_GL_DeleteContext(glContext);   
    SDL_DestroyWindow(window); 
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    // DELETE ALL VARIABLES CREATED WITH THE KEYWORD "new"
    delete level1;
    delete camera;
    delete input;
    delete rm;
    delete world;

    std::cout << "Program succeeded" << std::endl;
	return 0;
}

void CalculateFrameRate()
{
	float currentFrame = SDL_GetTicks();
	deltaTime = ((currentFrame - lastFrame) / 1000.0f);
	lastFrame = currentFrame;
    fpsCount++;
	totalTime += deltaTime;
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		//std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}
