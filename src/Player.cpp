#include "Player.h"

Player::Player(Engine::Math::Vec2f pos,SDL_Renderer* renderer,const char* path)
	: Entity(pos,renderer,path), forceJump(40), dT(0)
{
}

Player::~Player()
{
	//delete sprite;
}

void Player::update()
{
	if (this->velocity.y <= terminalVelocity)
		this->velocity += globalConfig->gravity;
	pos += this->velocity;
	movementLogic();
	sprite->box.x = pos.x;
	sprite->box.y = pos.y;
}

void Player::draw()
{
	if(SDL_RenderCopy(this->renderer, sprite->texture, &sprite->srcR, &sprite->box))
	{
		std::cout << "Failed rendering Player SDL_ERROR: " << SDL_GetError() << std::endl;
		exit(0);
	}
}

void Player::colided(Engine::InterfaceToColide* cause)
{
	Engine::SideColided side;
	SDL_Rect& cBox = cause->boxInfo();
	
	if (cause->type == Engine::TypeColision::WALL || cause->type == Engine::TypeColision::GROUND) {
		side = Engine::Colisor::calcRecColision(&sprite->box, &cBox);
		//Bottom
		if (side == Engine::SideColided::BOTTOM)
		{
			this->velocity.y = 0;
			pos.y = cBox.y + cBox.h;
		}
			
		//Left
		if (side == Engine::SideColided::LEFT)
			pos.x = cBox.x - sprite->box.h;

		//Right
		if (side == Engine::SideColided::RIGHT)
			pos.x = cBox.x + cBox.w;

		//Top
		if (side == Engine::SideColided::TOP)
		{
			this->velocity.y = 0;
			isJumping = false;
			pos.y = cBox.y - cBox.h;
		}	
	}
	sprite->box.x = pos.x;
	sprite->box.y = pos.y;
}

//Private
inline void Player::movementLogic()
{
	if (pos.y + sprite->box.h > globalConfig->windowSize.H)
		this->velocity.y = 0;

	keyboard->clicked(keyboard->ky::SPACEBAR, [&]()
	{
		this->sprite->box.x--;
	});

	keyboard->clicked(keyboard->ky::PLUS_KEY, [&]()
	{
		this->forceJump++;
		std::cout << "Force jump is: " << forceJump << std::endl;
	});

	keyboard->clicked(keyboard->ky::MINUS_KEY, [&]()
	{
		this->forceJump--;
		std::cout << "Force jump is: " << forceJump << std::endl;
	});

	if (keyboard->isPress(keyboard->ky::ARROW_RIGHT)) {
		if (pos.x + sprite->box.w < globalConfig->windowSize.W)
			pos.x += 10;//this->velocity.x;
	}
	if (keyboard->isPress(keyboard->ky::ARROW_LEFT)) {
		if (pos.x > 0)
			pos.x -= 10;//this->velocity.x;
	}

	keyboard->clicked(keyboard->ky::ARROW_UP, [&]()
	{
		if (pos.y > 0 && !isJumping) {
			this->velocity.y -= this->forceJump;
			isJumping = true;
		}
	});
}
