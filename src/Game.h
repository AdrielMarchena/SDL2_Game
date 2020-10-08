#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Keyboard.h"
#include "Colisor.h"

class interfaceDrawUpdate {
public:
	virtual void update()=0;
	virtual void draw()=0;
	
};

class interfaceDraw {
public:
	virtual void draw() = 0;
};

class Game{
public:
	SDL_Event* event;
	SDL_Window* window;
	std::vector<interfaceDrawUpdate*> objArrayDrawUpdate;
	std::vector<interfaceDraw*> objArrayDraw;
	SDL_Renderer* renderer;
	Keyboard* keyboard;
	std::vector<Colisions::Colisor*> c_Colisors;
	static int frameTime;
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
	void PushIntoArrayDrawUpdate(interfaceDrawUpdate* obj);
	void PushIntoArrayDraw(interfaceDraw* obj);
	void PushColisor(Colisions::Colisor* colisor);
	void initLoop();
	void stopLoop();
	void bindKeyboard(Keyboard* keyboard);
};

