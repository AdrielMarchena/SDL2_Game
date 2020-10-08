#include "Player.h"
#include "Keyboard.h"
#include "Game.h"

Player::Player(SDL_Renderer* renderer)
{
	xPosition = GLOBAL_SCREEN_W / 2;
	yPosition = GLOBAL_SCREEN_H / 2;

	dX = 1.0f;
	dY = 0.0f;
	PlayerBox.w = 64; 
	PlayerBox.h = 64;
	PlayerBox.x = (int)xPosition;
	PlayerBox.y = (int)yPosition;

	this->renderer = renderer;
	const char* pathImage = "assets/player.png";
	

	playerSurface = IMG_Load(pathImage);
	playerTexture = SDL_CreateTextureFromSurface(this->renderer, playerSurface);
	if (playerTexture == NULL) {
		std::cout << "Image < " << pathImage << " > Not Loaded!" << std::endl << "ERROR: " << SDL_GetError() << std::endl;
		return;
	}
	std::cout << "Image < " << pathImage << " > Loaded!" << std::endl;
	SDL_FreeSurface(playerSurface);
}

Player::~Player()
{
	SDL_DestroyTexture(playerTexture);
}

void Player::update()
{
	
	movementLogic();
	if(this->dY < terminalVelocity)
		this->dY += GLOBAL_GRAVITY_VALUE;
	this->PlayerBox.y += this->dY * Game::frameTime;
}

void Player::draw()
{
	if(SDL_RenderCopy(this->renderer, playerTexture, NULL, &PlayerBox))
	{
		std::cout << "Failed rendering Player SDL_ERROR: " <<SDL_GetError() << std::endl;
		exit(0);
	}
}

void Player::bindKeyboard(Keyboard* keyboard)
{
	this->keyboard = keyboard;
}

SDL_Rect& Player::boxInfo()
{
	if(PlayerBox.y + PlayerBox.h >= 600){ PlayerBox.y = 600 - PlayerBox.h; }
	return PlayerBox;
}

void Player::colided(Colisions::InterfaceToColide* cause)
{
	SDL_Rect& cBox = cause->boxInfo();
	if (cause->type == Colisions::Type::GROUND) {
		//Working
		if (PlayerBox.y + PlayerBox.h > cBox.y) {
			PlayerBox.y = cBox.y - PlayerBox.h;
			this->dY = 0;
			isJumping = false;
		}
	}
	if (cause->type == Colisions::Type::WALL) {
		//Working
		if (PlayerBox.y + PlayerBox.h > cBox.y) {
			PlayerBox.x = cBox.x - PlayerBox.w;
		}
	}
}

void Player::bindTypeColision(Colisions::Type type)
{
	this->type = type;
}

//Private
inline void Player::movementLogic()
{

	if (PlayerBox.y + PlayerBox.h > GLOBAL_SCREEN_H)
		this->dY = 0;

	keyboard->clicked(keyboard->ky::SPACEBAR, [&]()
	{
		this->PlayerBox.x--;
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
		if (PlayerBox.x + PlayerBox.w < GLOBAL_SCREEN_W)
			PlayerBox.x += dX;
	}
	if (keyboard->isPress(keyboard->ky::ARROW_LEFT)) {
		if (PlayerBox.x > 0)
			PlayerBox.x -= dX;
	}

	keyboard->clicked(keyboard->ky::ARROW_UP, [&]()
	{
		//if (PlayerBox.y > 0 && !isJumping) {
			this->dY -= this->forceJump * Game::frameTime;
			isJumping = true;
		//}
	});

	if (keyboard->isPress(keyboard->ky::ARROW_DOWN)) {
		if (PlayerBox.y + PlayerBox.h < GLOBAL_SCREEN_H)
			PlayerBox.y += dY;
	}
}
