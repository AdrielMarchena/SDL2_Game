#include "Game.h"

Game::Game(){}

Game::~Game() {}

void Game::init(const char* title, const int& xpos, const int& ypos, const int& width, const int& height, const bool& fullscrean) {
	
	int flags = 0;
	if (fullscrean)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	while (SDL_PollEvent(&keyboard->events)) {
		if (keyboard->events.type == SDL_QUIT) {
			this->stopLoop();
		}
		keyboard->handleInputs();
	}
}

void Game::update() {
	
	for (size_t i = 0; i < objArrayDrawUpdate.size(); i++)
		objArrayDrawUpdate[i]->update();
	
	for (size_t i = 0; i < c_Colisors.size(); i++)
		c_Colisors[i]->processColisions();
}

void Game::render() {
	SDL_RenderClear(this->renderer);

	for (size_t i = 0; i < objArrayDraw.size(); i++) {
		objArrayDraw[i]->draw();
	}
	for (size_t i = 0; i < objArrayDrawUpdate.size(); i++) {
		objArrayDrawUpdate[i]->draw();
	}
	SDL_RenderPresent(this->renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::PushIntoArrayDrawUpdate(interfaceDrawUpdate* obj)
{
	objArrayDrawUpdate.push_back(obj);
}

void Game::PushIntoArrayDraw(interfaceDraw* obj)
{
	objArrayDraw.push_back(obj);
}

void Game::PushColisor(Colisions::Colisor* colisor)
{
	c_Colisors.push_back(colisor);
}

void Game::initLoop()
{
	//short iterations = 0;
	//static unsigned long long cicleI = 0;
	const short FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = NULL;

	while (this->isRunning) {

		this->handleEvents();
		this->update();
		this->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
		/*if (iterations >= SHRT_MAX) {
			iterations = 0;
			cicleI++;
		}
		iterations++;*/
	}
	//std::cout << "actual iteractions: " << iterations << std::endl << "Cicles: " << cicleI << std::endl;
	this->clean();
}

void Game::stopLoop()
{
	
	this->isRunning = false;

}

void Game::bindKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}
