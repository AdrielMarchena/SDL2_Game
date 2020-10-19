#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Keyboard.h"
#include "Colisor.h"
#include "Global.h"
#include "MinorEntity.h"
#include "Entity.h"

namespace Engine
{
	class Game {
	private:
		bool isRunning;

		GlobalConf GLOBAL_CONF;
		SDL_Window* window;
		std::vector<Entity*> objArrayDrawUpdate;
		std::vector<MinorEntity*> objArrayDraw;
		SDL_Renderer* renderer;
		Keyboard* keyboard;
		std::vector<Colisor*> c_Colisors;

	public:
		Game();
		~Game();

		Game(const char* title, int xpos, int ypos, int width, int height, bool fullscrean);

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
		void fullscreen(bool opc);
		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();
		Keyboard* getKeyboard();
		GlobalConf* getGlobalConf();
	};
}

