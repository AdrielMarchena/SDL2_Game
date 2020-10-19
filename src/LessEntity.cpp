#include "LessEntity.h"

LessEntity::LessEntity(Engine::Math::Vec2f pos ,SDL_Renderer* renderer,const char* pathImage)
	: MinorEntity(pos,renderer,pathImage)
{
}

LessEntity::~LessEntity()
{
	//delete sprite;
}

SDL_Rect& LessEntity::boxInfo()
{
	return sprite->box;
}

void LessEntity::colided(InterfaceToColide* cause)
{
	return;
}

void LessEntity::draw()
{
	if(SDL_RenderCopy(this->renderer, sprite->texture, NULL, &sprite->box))
	{
		std::cout << "Failed rendering Less Entity SDL_ERROR: " << SDL_GetError() << std::endl;
		exit(0);
	}
}

void LessEntity::bindTypeColision(Engine::TypeColision type)
{
	this->type = type;
}

