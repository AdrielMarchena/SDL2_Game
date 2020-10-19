#include "Player.h"

Player::Player(Engine::Math::Vec2f pos,SDL_Renderer* renderer,const char* path)
	: Entity(pos,renderer,path), forceJump(40)
{
	dX = 10;
}

Player::~Player()
{
	//delete sprite;
}

void Player::update()
{
	if (this->dY <= terminalVelocity)
		this->dY += globalConfig->gravity;
	pos.y += this->dY;
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
			pos.y = cBox.y + cBox.h;

		//Left
		if (side == Engine::SideColided::LEFT)
			pos.x = cBox.x - sprite->box.h;

		//Right
		if (side == Engine::SideColided::RIGHT)
			pos.x = cBox.x + cBox.w;

		//Top
		if (side == Engine::SideColided::TOP)
		{
			dY = 0;
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
		this->dY = 0;

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
			pos.x += dX;
	}
	if (keyboard->isPress(keyboard->ky::ARROW_LEFT)) {
		if (pos.x > 0)
			pos.x -= dX;
	}

	keyboard->clicked(keyboard->ky::ARROW_UP, [&]()
	{
		if (pos.y > 0 && !isJumping) {
			this->dY -= this->forceJump;
			isJumping = true;
		}
	});

	/*if (keyboard->isPress(keyboard->ky::ARROW_DOWN)) {
		if (PlayerBox.y + PlayerBox.h < GLOBAL_SCREEN_H)
			this->PlayerBox.y++;
	}*/
}
