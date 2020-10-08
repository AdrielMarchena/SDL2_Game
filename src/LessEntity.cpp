#include "LessEntity.h"

LessEntity::LessEntity(){}

LessEntity::LessEntity(SDL_Renderer* renderer,const char* pathImage)
{

	objBox.h = 64; 
	objBox.w = 64; 
	objBox.x = 0; 
	objBox.y = GLOBAL_SCREEN_H - 64;

	this->renderer = renderer;
	objSurface = IMG_Load(pathImage);
	objTexture = SDL_CreateTextureFromSurface(this->renderer, objSurface);
	if (objTexture == NULL) {
		std::cout << "Image < " << pathImage << " > Not Loaded!" << std::endl << "ERROR: " << SDL_GetError() << std::endl;
		return;
	}
		
	SDL_FreeSurface(objSurface);
	std::cout << "Image < " << pathImage << " > Loaded!" << std::endl;

}

LessEntity::~LessEntity()
{
	//SDL_DestroyTexture(objTexture);
}

SDL_Rect& LessEntity::boxInfo()
{
	return objBox;
}

void LessEntity::colided(InterfaceToColide* cause)
{
	return;
}

void LessEntity::draw()
{
	if(SDL_RenderCopy(this->renderer, objTexture, NULL, &objBox))
	{
		std::cout << "Failed rendering Less Entity SDL_ERROR: " << SDL_GetError() << std::endl;
		exit(0);
	}
}

void LessEntity::bindTypeColision(Colisions::Type type)
{
	this->type = type;
}

