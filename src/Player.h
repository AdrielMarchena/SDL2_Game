#pragma once
#include "Game.h"
#include "Colisor.h"
#include "GlobalDefs.h"
class Player : public interfaceDrawUpdate, public Colisions::InterfaceToColide
{
public:
	float dX, dY;
	int forceJump;
	int terminalVelocity = 20;
	bool isJumping;
	float xPosition;
	float yPosition;
public:
	SDL_Renderer* renderer;
	SDL_Texture* playerTexture;
	SDL_Rect srcR, PlayerBox;
	SDL_Surface* playerSurface;
	Keyboard* keyboard;

public:
	
	Player(SDL_Renderer* renderer);
	~Player();

	//From InterfaceToEngine
	void update();
	void draw();
	
	void bindKeyboard(Keyboard* keyboard);
	//From InterfaceToColide
	SDL_Rect& boxInfo();
	void colided(InterfaceToColide* cause);
	void bindTypeColision(Colisions::Type type);
private:
	inline void movementLogic();

};


