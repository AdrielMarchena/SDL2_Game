#pragma once
#include "Engine/Game.h"
#include "Engine/Sprite.h"
#include "Engine/MinorEntity.h"
#include "Engine/InterfaceToColide.h"
#include "Engine/Math.h"

class LessEntity 
	: public Engine::MinorEntity, public Engine::InterfaceToColide
{
public:
	LessEntity() {};
	LessEntity(Engine::Math::Vec2f pos, SDL_Renderer* renderer, const char* pathImage);
	~LessEntity();

	//Todo: Setters for position

	SDL_Rect& boxInfo();
	void colided(InterfaceToColide* cause);

	void draw();
	void bindTypeColision(Engine::TypeColision type);

};

