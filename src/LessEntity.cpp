#include "LessEntity.h"

LessEntity::LessEntity(){}

LessEntity::LessEntity(SDL_Renderer* renderer,const char* pathImage)
	: renderer(renderer)
{

	sprite = new Engine::Sprite(renderer, pathImage);

	sprite->box.h = 64;
	sprite->box.w = 64;
	sprite->box.x = 0;
	sprite->box.y = GLOBAL_SCREEN_H - 64;

}

LessEntity::~LessEntity()
{
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

