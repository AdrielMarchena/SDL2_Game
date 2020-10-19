#include "MinorEntity.h"

namespace Engine
{
	MinorEntity::MinorEntity(Math::Vec2f pos, SDL_Renderer* renderer, const char* path)
		: renderer(renderer)
	{
		this->sprite = new Engine::Sprite(renderer, path);
		if (sprite)
		{
			sprite->box.w = 64;
			sprite->box.h = 64;
			sprite->box.x = (int)pos.x;
			sprite->box.y = (int)pos.y;
		}
		else {
			std::cout << "Failed while trying to create entity sprite" << std::endl;
		}
	}

	MinorEntity::~MinorEntity()
	{
		//delete sprite;
	}

	void MinorEntity::draw()
	{
		if (SDL_RenderCopy(this->renderer, sprite->texture, &sprite->srcR, &sprite->box))
		{
			std::cout << "Failed rendering Entity SDL_ERROR: " << SDL_GetError() << std::endl;
			exit(0);
		}
	}

	void MinorEntity::bindRenderer(SDL_Renderer* renderer)
	{
		if (renderer)
			this->renderer = renderer;
		else
			std::cout << "Cold not bind renderer into Entity, renderer is null" << std::endl;
	}

	Math::Vec2f& MinorEntity::getPos()
	{
		return pos;
	}

	void MinorEntity::setPos(Engine::Math::Vec2f pos)
	{
		this->pos = pos;
	}

	Sprite* MinorEntity::getSprite()
	{
		return sprite;
	}
	void MinorEntity::setGlobalConfig(GlobalConf* globalConfig)
	{
		this->globalConfig = globalConfig;
	}
}


