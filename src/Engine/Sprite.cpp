#include "Sprite.h"
#include <iostream>

namespace Engine {

	Sprite::Sprite(SDL_Renderer* renderer, const char* path)
		:box({0,0,0,0}), srcR({ 0,0,0,0 })
	{
		SDL_Surface* surface = IMG_Load(path);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			std::cout << "Image < " << path << " > Not Loaded!" << std::endl << "ERROR: " << SDL_GetError() << std::endl;
			return;
		}
		srcR.w = surface->w;
		srcR.h = surface->h;
		//std::cout << "Image < " << path << " > Loaded!" << std::endl;
		SDL_FreeSurface(surface);
	}

	Sprite::~Sprite(){}

}