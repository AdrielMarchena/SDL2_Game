#pragma once
#include "SDL_image.h"
#include "Engine/Colisor.h"
#include "Engine/GlobalDefs.h"
#include "Engine/Keyboard.h"
#include "Engine/InterfaceDrawUpdate.h"
#include "Engine/InterfaceToColide.h"
#include "Engine/Sprite.h"

class Player : public Engine::interfaceDrawUpdate, public Engine::InterfaceToColide
{
public:
	float dX, dY;
	int forceJump;
	int terminalVelocity = 20;
	bool isJumping;
	float xPosition;
	float yPosition;
private:
	SDL_Renderer* renderer;
	Engine::Keyboard* keyboard;
	Engine::Sprite* sprite;

public:
	
	Player(SDL_Renderer* renderer, const char* path);
	~Player();

	//From InterfaceToEngine
	void update();
	void draw();
	
	void bindKeyboard(Engine::Keyboard* keyboard);
	void bindRenderer(SDL_Renderer* renderer);
	//From InterfaceToColide
	SDL_Rect& boxInfo();
	void colided(InterfaceToColide* cause);
	void bindTypeColision(Engine::TypeColision type);
private:
	inline void movementLogic();
};


