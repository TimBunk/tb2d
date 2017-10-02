#include "game.h"
#include "camera.h"

const float screenWidth = 800, screenHeight = 600;
Camera* camera;
SDL_Window* window;
bool quit;
SDL_GLContext glContext;

Shader* shader;

Text* text;
ResourceManager* rm;

b2World* world;
std::vector<Box*> boxes;
Box* ground;
Circle* circle;

double mouseX;
double mouseY;

Game* game;
Input* input;
Player* player;

float Configure::M2P = 50;
float Configure::P2M = 1 / Configure::M2P;

int main() {
	camera = new Camera(screenWidth, screenHeight);
	game = new Game(camera);
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
	            ground = new Box(screenWidth / 2, screenHeight, screenWidth, 30, false, Configure::P2M, world, camera->GetProjectionMatrix());
	            circle = new Circle(400, 0, 50, true, Configure::P2M, world, camera->GetProjectionMatrix());

	            rm = new ResourceManager();
	            rm->CreateShader("shader", "shaders//shader.vs", "shaders//shader.fs");
	            shader = rm->GetShader("shader");

	            shader->Use();
	            shader->SetMatrix4("projection", camera->GetProjectionMatrix());

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

	            text = new Text("fonts/OpenSans-Regular.ttf", "Hello world", 100, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), true, 300, 100, camera->GetProjectionMatrix());
	            text->SetPosition(glm::vec3(screenWidth/2, screenHeight-100, 0.0f));
	            text->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	            text->SetFontSize(100);
	            text->DrawHUD();

	            // THE GAME LOOP
	            while (!input->Quit()) {
	            	game->Update();
					// Checks for key input
					if (input->KeyPress(SDL_SCANCODE_T)) {
						Box* box;
						box = new Box(mouseX, mouseY, 50, 50, true, Configure::P2M, world, camera->GetProjectionMatrix());
						boxes.push_back(box);
					}
					mouseX = input->GetMousePositionScreenSpace().x;
					mouseY = input->GetMousePositionScreenSpace().y;
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
	                circle->Draw(camera->GetViewMatrix(), shader, Configure::M2P);
	                for (int i = 0; i < boxes.size(); i++) {
	                    shader->Use();
	                    boxes[i]->Draw(camera->GetViewMatrix(), shader, Configure::M2P);
	                }
	                // draw the ground
	                shader->Use();
	                glActiveTexture(GL_TEXTURE0 + texture.id);
	                shader->SetInt("ourTexture", texture.id);
	                glBindTexture(GL_TEXTURE_2D, texture.id);
	                glActiveTexture(GL_TEXTURE0);

	                ground->Draw(camera->GetViewMatrix(), shader, Configure::M2P);
	                // Draw text
	                text->DrawHUD();
	                //game->Update();

	                // Update window with OpenGL rendering
	                SDL_GL_SwapWindow(window);
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
		delete camera;
		delete text;
		delete rm;
		delete input;
		delete player;
		delete game;
		while (boxes.size() > 0) {
			int i = boxes.size() - 1;
			delete boxes[i];
			boxes.pop_back();
		}
		std::cout << "Program succeeded" << std::endl;

	return 0;
}

Game::Game(Camera* camera) : Scene::Scene(camera) {
	player = new Player(world, camera);
}

void Game::Update() {
	this->CalculateDeltaTime();
	this->UpdateChilderen(this, this->deltaTime);
	input->Update();
	//player->Update(deltaTime);

	// update box2D world
	world->Step(deltaTime, 8, 3);
}
