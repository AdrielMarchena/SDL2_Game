#pragma once
#include "SDL_image.h"
#include "Engine/Colisor.h"
#include "Engine/GlobalDefs.h"
#include "Engine/Keyboard.h"
#include "Engine/Entity.h"
#include "Engine/InterfaceToColide.h"
#include "Engine/Sprite.h"

class Player : public Engine::Entity
{
public:
	int forceJump;
	int terminalVelocity = 20;
	bool isJumping = false;

public:
	
	Player(Engine::Math::Vec2f pos,SDL_Renderer* renderer, const char* path);
	~Player();
	
	virtual void update();
	virtual void draw();
	
	void colided(InterfaceToColide* cause);
private:
	inline void movementLogic();
};


