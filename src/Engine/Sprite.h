#pragma once
#include "SDL_image.h"

namespace Engine {
	class Sprite
	{
	public:
		SDL_Texture* texture;
		SDL_Rect srcR, box;

		//Sprite();
		Sprite(SDL_Renderer* renderer,const char* path);
		~Sprite();
	};
}

