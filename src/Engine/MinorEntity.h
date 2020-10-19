#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Math.h"
#include "Global.h"

namespace Engine
{
	class MinorEntity {
	protected:
		GlobalConf* globalConfig;
		Math::Vec2f pos;
		SDL_Renderer* renderer;
		Sprite* sprite;

	public:
		MinorEntity() {};
		MinorEntity(Math::Vec2f pos, SDL_Renderer* renderer, const char* path);
		~MinorEntity();

		virtual void draw();

		void bindRenderer(SDL_Renderer* renderer);

		Math::Vec2f& getPos();
		void setPos(Engine::Math::Vec2f pos);
		Sprite* getSprite();
		void setGlobalConfig(GlobalConf* globalConfig);
	};
}