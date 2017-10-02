#define GLEW_STATIC
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "scene.h"
#include "camera.h"
#include "text.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

const float screenWidth = 800, screenHeight = 600;
SDL_Window* window;
SDL_GLContext glContext;
bool quit;

Camera* camera;
Input* input;

int main() {
	camera = new Camera(screenWidth, screenHeight);
	input = new Input();

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
        window = SDL_CreateWindow("The Restless Tombs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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

            // THE GAME LOOP
            int i = 0;
            while (!input->Quit()) {
                // Set background color
                glClearColor(0, 0.5, 0.5, 1);
                // Clear color buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                // Update the keyboard/mouse input
                input->Update();
                
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
    delete camera;
    delete input;

    std::cout << "Program succeeded" << std::endl;
	return 0;
}
