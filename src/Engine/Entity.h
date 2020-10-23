#pragma once
#include <SDL.h>
#include "Keyboard.h"
#include "Sprite.h"
#include "Math.h"
#include "InterfaceToColide.h"
#include "MinorEntity.h"

namespace Engine
{
	class Entity : public MinorEntity, public InterfaceToColide {
	protected:
		Math::Vec2f velocity;
		Keyboard* keyboard;
		
	public:
		Entity() {};
		Entity(Math::Vec2f pos,SDL_Renderer* renderer, const char* path);
		~Entity();

		virtual void update();
		void bindKeyboard(Keyboard* keyboard);

		SDL_Rect& boxInfo();
		void colided(InterfaceToColide* cause);
		void bindColisionType(TypeColision type);

		Math::Vec2f getVelocity();
	};
}
