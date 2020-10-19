#include <iostream>
#include <random>
#include "Engine/Game.h"
#include "Engine/Colisor.h"
#include "Player.h"
#include "LessEntity.h"
#include "Utils/HandleFile.h"

bool ColisionRect(const SDL_Rect& sub, const SDL_Rect& other) {

    if ((sub.x + sub.w) > other.x &&
        sub.x < (other.x + other.w) &&
        (sub.y + sub.h) > other.y &&
        sub.y < (other.y + other.h))
    {
        return true;
    }

    return false;
}

int main(int argc, char* argv[])
{
    using namespace Engine;
    using namespace Utils;

    //Create keyboard instance 
    Keyboard* keyboard = new Keyboard();

    //Create game instance
    Game* game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
    //Bind a keyboard to the game instance
    game->bindKeyboard(keyboard);

    //create a colisor instance
    Colisor* colisionPlayerGround = new Colisor();
    //Set the colisor mode to First to all mode
    colisionPlayerGround->setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);

    //Create a player instance
    Player* player = new Player({300,300}, game->getRenderer(), "assets/player.png");
    player->bindColisionType(TypeColision::PLAYER);
    //Bind a colision to the player
    //The player need to be the first 
    colisionPlayerGround->pushNewItem(player);

    //Bind Keyboard to the player
    player->bindKeyboard(keyboard);

    //bind a function to the colisor
    colisionPlayerGround->setMethodToColide(ColisionRect);

    //Create some grounds
    const unsigned short lGround = 20;
    LessEntity* ground = new LessEntity[lGround];
    int positionX = 0;
    //define some grounds
    for (int i = 0; i < lGround; i++) {

        ground[i] = LessEntity({ (float)positionX, (float)game->getGlobalConf()->windowSize.H -64}, game->getRenderer(), "assets/ground.png");
        //ground[i].sprite->box.y -= std::rand() % 10;
        game->PushIntoArrayDraw(&ground[i]);
        colisionPlayerGround->pushNewItem(&ground[i]);
        ground[i].bindTypeColision(TypeColision::GROUND);
        positionX += ground[i].boxInfo().w;

    }

    //Colision for walls
    Colisor* colisionPlayerWall = new Colisor();
    colisionPlayerWall->setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);
    colisionPlayerWall->setMethodToColide(ColisionRect);
    colisionPlayerWall->pushNewItem(player);

    //Create some walls
    const unsigned short lWall = 1;
    LessEntity* wall = new LessEntity[lWall];
    positionX = 0;
    for (int i = 0; i < lWall; i++) {

        wall[i] = LessEntity({ game->getGlobalConf()->windowSize.W / 2,game->getGlobalConf()->windowSize.H / 2 }, game->getRenderer(), "assets/wall.png");
        game->PushIntoArrayDraw(&wall[i]);
        colisionPlayerWall->pushNewItem(&wall[i]);
        wall[i].bindTypeColision(TypeColision::WALL);
        positionX += wall[i].getSprite()->box.h;
    }

    //Push the player into the game loop
    game->PushIntoArrayDrawUpdate(player);

    game->PushColisor(colisionPlayerGround);
    game->PushColisor(colisionPlayerWall);
    //Init game loop
    game->initLoop();

    //delete everything on the heap here
    delete keyboard;
    delete[] wall;
    delete[] ground;
    delete player;
    delete game;
    delete colisionPlayerGround;
    delete colisionPlayerWall;

    return 0;
}