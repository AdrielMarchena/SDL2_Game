#include "Player.h"

Player::Player(SDL_Renderer* renderer,const char* path)
	: renderer(renderer)
{
	xPosition = GLOBAL_SCREEN_W / 2;
	yPosition = GLOBAL_SCREEN_H / 2;

	dX = 1.0f;
	dY = 0.0f;
	
	this->sprite = new Engine::Sprite(renderer, path);
	if (sprite)
	{
		sprite->box.w = 64;
		sprite->box.h = 64;
		sprite->box.x = (int)xPosition;
		sprite->box.y = (int)yPosition;
	}
	else {
		std::cout << "Failed while trying to create player sprite" << std::endl;
	}
}

Player::~Player()
{
	//delete(sprite);
}

void Player::update()
{
	if (this->dY <= terminalVelocity)
		this->dY += GLOBAL_GRAVITY_VALUE;
	this->sprite->box.y += this->dY;
	movementLogic();
	
}

void Player::draw()
{
	if(SDL_RenderCopy(this->renderer, sprite->texture, NULL, &sprite->box))
	{
		std::cout << "Failed rendering Player SDL_ERROR: " <<SDL_GetError() << std::endl;
		exit(0);
	}
}

void Player::bindKeyboard(Engine::Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

void Player::bindRenderer(SDL_Renderer* renderer)
{
	if(renderer != nullptr)
		this->renderer = renderer;
}

SDL_Rect& Player::boxInfo()
{
	return sprite->box;
}

void Player::colided(Engine::InterfaceToColide* cause)
{
	Engine::SideColided side;
	SDL_Rect& cBox = cause->boxInfo();
	
	if (cause->type == Engine::TypeColision::WALL || cause->type == Engine::TypeColision::GROUND) {
		side = Engine::Colisor::calcRecColision(&sprite->box, &cBox);
		//Bottom
		if (side == Engine::SideColided::BOTTOM)
			sprite->box.y = cBox.y + cBox.h;

		//Left
		if (side == Engine::SideColided::LEFT)
			sprite->box.x = cBox.x - sprite->box.h;

		//Right
		if (side == Engine::SideColided::RIGHT)
			sprite->box.x = cBox.x + cBox.w;

		//Top
		if (side == Engine::SideColided::TOP)
			sprite->box.y = cBox.y - cBox.h;
	}
}

void Player::bindTypeColision(Engine::TypeColision type)
{
	this->type = type;
}

//Private
inline void Player::movementLogic()
{

	if (sprite->box.y + sprite->box.h > GLOBAL_SCREEN_H)
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
		if (sprite->box.x + sprite->box.w < GLOBAL_SCREEN_W)
			sprite->box.x += dX;
	}
	if (keyboard->isPress(keyboard->ky::ARROW_LEFT)) {
		if (sprite->box.x > 0)
			sprite->box.x -= dX;
	}

	keyboard->clicked(keyboard->ky::ARROW_UP, [&]()
	{
		if (sprite->box.y > 0 && !isJumping) {
			this->dY -= this->forceJump;
			isJumping = true;
		}
	});

	/*if (keyboard->isPress(keyboard->ky::ARROW_DOWN)) {
		if (PlayerBox.y + PlayerBox.h < GLOBAL_SCREEN_H)
			this->PlayerBox.y++;
	}*/
}
