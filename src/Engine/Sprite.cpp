#include "Sprite.h"
#include <iostream>

namespace Engine {

	Sprite::Sprite(SDL_Renderer* renderer, const char* path)
	{
		SDL_Surface* surface = IMG_Load(path);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			std::cout << "Image < " << path << " > Not Loaded!" << std::endl << "ERROR: " << SDL_GetError() << std::endl;
			return;
		}
		std::cout << "Image < " << path << " > Loaded!" << std::endl;
		SDL_FreeSurface(surface);
	}

}