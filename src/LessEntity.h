#pragma once
#include "Game.h"
#include "GlobalDefs.h"
#include "Colisor.h"
class LessEntity 
	: public interfaceDraw, public Colisions::InterfaceToColide 
{
public:
	SDL_Renderer* renderer;
	SDL_Texture* objTexture;
	SDL_Rect objBox;
	SDL_Surface* objSurface;
	Keyboard* keyboard = nullptr;

	LessEntity();
	LessEntity(SDL_Renderer* renderer, const char* pathImage);
	~LessEntity();

	SDL_Rect& boxInfo();
	void colided(InterfaceToColide* cause);

	void draw();
	void bindTypeColision(Colisions::Type type);
};

