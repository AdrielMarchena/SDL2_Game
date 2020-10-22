#include "Game.h"
#include "SDL_events.h"

namespace Engine
{
	Game::Game() {}

	Game::~Game() {}

	Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
	{
		GLOBAL_CONF.windowSize.W = width;
		GLOBAL_CONF.windowSize.H = height;

		int flags = 0;
		GLOBAL_CONF.fScreen = false;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
			GLOBAL_CONF.fScreen = true;
		}
			
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			std::cout << "Subsystem Initialised" << std::endl;

			window = SDL_CreateWindow(title, xpos, ypos, GLOBAL_CONF.windowSize.W, GLOBAL_CONF.windowSize.H, flags);
			if (window) {
				std::cout << "Window created!" << std::endl;
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
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

	void Game::handleEvents()
	{
		while (SDL_PollEvent(&keyboard->events)) {
			keyboard->handleInputs();
		}
		globalKeys();
	}

	void Game::update() 
	{
		for (size_t i = 0; i < objArrayDrawUpdate.size(); i++)
			objArrayDrawUpdate[i]->update();

		for (size_t i = 0; i < c_Colisors.size(); i++)
			c_Colisors[i]->processColisions();
	}

	void Game::render() 
	{
		SDL_RenderClear(this->renderer);

		for (size_t i = 0; i < objArrayDraw.size(); i++) {
			objArrayDraw[i]->draw();
		}
		for (size_t i = 0; i < objArrayDrawUpdate.size(); i++) {
			objArrayDrawUpdate[i]->draw();
		}
		SDL_RenderPresent(this->renderer);
	}

	void Game::clean() 
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		std::cout << "Game cleaned" << std::endl;
	}

	void Game::PushIntoArrayDrawUpdate(Entity* obj)
	{
		objArrayDrawUpdate.push_back(obj);
		obj->setGlobalConfig(&GLOBAL_CONF);
	}

	void Game::PushIntoArrayDraw(MinorEntity* obj)
	{
		objArrayDraw.push_back(obj);
		obj->setGlobalConfig(&GLOBAL_CONF);
	}

	void Game::PushColisor(Colisor* colisor)
	{
		c_Colisors.push_back(colisor);
	}

	void Game::initLoop()
	{
		const short FPS = 60;
		const int frameDelay = 1000 / FPS;

		Uint32 frameStart = NULL;
		int frameTime = NULL;
		while (this->isRunning) {

			frameStart = SDL_GetTicks();
			this->handleEvents();
			this->update();
			this->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
			
		}
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

	void Game::fullscreen(bool opc)
	{
		if (opc)
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		}
		else
		{
			SDL_SetWindowFullscreen(window, 0);
		}

		GLOBAL_CONF.fScreen = !GLOBAL_CONF.fScreen;
	}

	SDL_Window* Game::getWindow()
	{
		return window;
	}

	SDL_Renderer* Game::getRenderer()
	{
		return renderer;
	}

	Keyboard* Game::getKeyboard()
	{
		return keyboard;
	}

	GlobalConf* Game::getGlobalConf()
	{
		return &GLOBAL_CONF;
	}

	inline void Game::globalKeys()
	{
		int key = keyboard->events.key.keysym.sym;
		if (keyboard->events.type == SDL_QUIT || key == SDLK_ESCAPE)
		{
			this->stopLoop();
		}
		keyboard->clicked(keyboard->F11_KEY, [&]() 
		{
			fullscreen(!GLOBAL_CONF.fScreen);
		});
	}

}