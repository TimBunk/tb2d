/*#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "shader.h"
#include "box.h"
#include "circle.h"
#include "texture.h"
#include "scene.h"
#include "camera.h"
#include "text.h"
#include "resourceManager.h"
#include "configure.h"

#include <GL/glew.h>
#include <glm-0.9.8.4/glm/glm.hpp>
#include <glm-0.9.8.4/glm/gtc/matrix_transform.hpp>
#include <glm-0.9.8.4/glm/gtc/type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const float screenWidth = 800, screenHeight = 600;
SDL_Window* window;
bool quit;
SDL_GLContext glContext;
SDL_Event sdlEvent;

b2World* world;
const float m2p = 50;
const float p2m = 1 / m2p;
std::vector<Box*> boxes;
Box* ground;
Circle* circle;

double mouseX;
double mouseY;

Shader* shader;
glm::mat4 projection;
Camera* cam;
Text* text;
ResourceManager* rm;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float totalTime = 0.0f;
int fpsCount = 0;
void CalculateFrameRate();

float Configure::M2P = 50;
float Configure::P2M = 1 / Configure::M2P;

int main() {
	std::cout << "M2P = " << Configure::M2P << std::endl;
	std::cout << "P2M = " << Configure::P2M << std::endl;
    mouseX = 0;
    mouseY = 0;

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
        window = SDL_CreateWindow("The true TB2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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



            world = new b2World(b2Vec2(0.0f, 9.91f));

            projection = glm::ortho(0.0f, screenWidth, screenHeight, 0.0f, -50.0f, 50.0f);

            rm = new ResourceManager();
            rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
            shader = rm->GetShader("shader");

            cam = new Camera(screenWidth, screenHeight);
            shader->Use();
            shader->SetMatrix4("projection", projection);

            //Texture texture = Tex::LoadTexture("textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
            rm->CreateTexture("container", "textures/container.jpg", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
            Texture texture = rm->GetTexture("container");
            glActiveTexture(GL_TEXTURE0 + texture.id);
            shader->SetInt("ourTexture", texture.id);
            glBindTexture(GL_TEXTURE_2D, texture.id);
            glActiveTexture(GL_TEXTURE0);

            //Texture texture2 = Tex::LoadTexture("textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
            rm->CreateTexture("awesomeFace", "textures/awesomeface.png", TextureWrap::repeat, TextureFilter::linear, TextureType::diffuse);
            Texture texture2 = rm->GetTexture("awesomeFace");
            glActiveTexture(GL_TEXTURE0 + texture2.id);
            shader->SetInt("ourTexture", texture2.id);
            glBindTexture(GL_TEXTURE_2D, texture2.id);
            glActiveTexture(GL_TEXTURE0);

            ground = new Box(screenWidth / 2, screenHeight, screenWidth, 30, false, p2m, world, projection);

            circle = new Circle(400, 0, 50, true, p2m, world, projection);

            text = new Text("fonts/OpenSans-Regular.ttf", "Hello world", 100, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true, 300, 100, cam->GetProjectionMatrix());
            text->SetPosition(glm::vec3(screenWidth/2, screenHeight-100, 0.0f));
            text->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
            text->SetFontSize(100);
            text->DrawHUD();

            // THE GAME LOOP
            while (!quit) {
                while(SDL_PollEvent(&sdlEvent) != 0) {
                    // Closes the window
                    if(sdlEvent.type == SDL_QUIT) {
                        quit = true;
                    }
                    // Checks for key input
                    else if (sdlEvent.type == SDL_KEYDOWN) {
                        switch (sdlEvent.key.keysym.sym) {
                            case SDLK_t:
                                Box* box;
                                box = new Box(mouseX, mouseY, 50, 50, true, p2m, world, projection);
                                boxes.push_back(box);
                        }
                    }
                    else if (sdlEvent.type == SDL_MOUSEMOTION) {
                        mouseX = sdlEvent.button.x;
                        mouseY = sdlEvent.button.y;
                    }
                }
                // Set background color as cornflower blue
                glClearColor(0, 0.5, 0.5, 1);
                // Clear color buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                shader->Use();

                glActiveTexture(GL_TEXTURE0 + texture2.id);
                shader->SetInt("ourTexture", texture2.id);
                glBindTexture(GL_TEXTURE_2D, texture2.id);
                glActiveTexture(GL_TEXTURE0);

                shader->Use();
                circle->Draw(cam->GetViewMatrix(), shader, m2p);
                for (int i = 0; i < boxes.size(); i++) {
                    shader->Use();
                    boxes[i]->Draw(cam->GetViewMatrix(), shader, m2p);
                }
                // draw the ground
                shader->Use();
                glActiveTexture(GL_TEXTURE0 + texture.id);
                shader->SetInt("ourTexture", texture.id);
                glBindTexture(GL_TEXTURE_2D, texture.id);
                glActiveTexture(GL_TEXTURE0);

                ground->Draw(cam->GetViewMatrix(), shader, m2p);
                // Draw text
                text->DrawHUD();
                // update box2D world
                world->Step(deltaTime, 8, 3);

                // Update window with OpenGL rendering
                SDL_GL_SwapWindow(window);
                CalculateFrameRate();
            }// THE END OF THE GAME LOOP
        }
    }
    // CLEAR ALL ALLOCATED MEMORY
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	delete ground;
	//delete shader;
	delete circle;
	delete cam;
	delete text;
	delete rm;
	while (boxes.size() > 0) {
		int i = boxes.size() - 1;
		delete boxes[i];
		boxes.pop_back();
	}
	std::cout << "Program succeeded" << std::endl;
	return 0;
}

// CALCULATE DELTATIME AND FRAMERATE
void CalculateFrameRate()
{
	float currentFrame = SDL_GetTicks();
	deltaTime = ((currentFrame - lastFrame) / 1000.0f);
	lastFrame = currentFrame;
    fpsCount++;
	totalTime += deltaTime;
	if (totalTime >= 1.0f) {
		totalTime -= 1.0f;
		std::cout << "fps: " << fpsCount << std::endl;
		fpsCount = 0;
	}
}*/
