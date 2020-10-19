#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Keyboard.h"
#include "Colisor.h"

#include "Entity.h"
#include "MinorEntity.h"

namespace Engine
{
	class Game {
	public:
		SDL_Event* event;
		SDL_Window* window;
		std::vector<Entity*> objArrayDrawUpdate;
		std::vector<MinorEntity*> objArrayDraw;
		SDL_Renderer* renderer;
		Keyboard* keyboard;
		std::vector<Colisor*> c_Colisors;
	private:
		bool isRunning;

	public:
		Game();
		~Game();

		void init(const char* title, const int& xpos, const int& ypos, const int& width, const int& height, const bool& fullscrean);
		void handleEvents();
		void update();
		void render();
		void clean();
		void PushIntoArrayDrawUpdate(Entity* obj);
		void PushIntoArrayDraw(MinorEntity* obj);
		void PushColisor(Colisor* colisor);
		void initLoop();
		void stopLoop();
		void bindKeyboard(Keyboard* keyboard);
	};
}

