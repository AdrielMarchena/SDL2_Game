#include "Entity.h"

namespace Engine
{
	Entity::Entity(Math::Vec2f pos, SDL_Renderer* renderer, const char* path)
		: MinorEntity(pos,renderer,path), keyboard(NULL), dX(1.0f), dY(0.0f)
	{
		
	}

	Entity::~Entity()
	{
		//delete sprite;
	}

	void Entity::update()
	{
	}
	
	void Entity::bindKeyboard(Engine::Keyboard* keyboard)
	{
		this->keyboard = keyboard;
	}
	
	SDL_Rect& Entity::boxInfo()
	{
		return sprite->box;
	}
	
	void Entity::colided(InterfaceToColide* cause)
	{
	}

	void Entity::bindColisionType(TypeColision type)
	{
		this->type = type;
	}
	
	float Entity::getDX()
	{
		return dX;
	}
	
	float Entity::getDY()
	{
		return dY;
	}
	
}