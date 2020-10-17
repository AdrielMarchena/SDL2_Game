#pragma once
#include "Engine/Game.h"
#include "Engine/GlobalDefs.h"

#include "Engine/InterfaceDraw.h"
#include "Engine/InterfaceToColide.h"

class LessEntity 
	: public Engine::interfaceDraw, public Engine::InterfaceToColide
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* objTexture;
	SDL_Rect objBox;
	SDL_Surface* objSurface;
	Engine::Keyboard* keyboard = nullptr;

	LessEntity();
	LessEntity(SDL_Renderer* renderer, const char* pathImage);
	~LessEntity();

	SDL_Rect& boxInfo();
	void colided(InterfaceToColide* cause);

	void draw();
	void bindTypeColision(Engine::TypeColision type);
};

