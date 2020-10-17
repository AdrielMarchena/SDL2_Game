#include <iostream>
#include "Engine/GlobalDefs.h"
#include "Engine/Game.h"
#include "Engine/Colisor.h"
#include "Player.h"
#include "LessEntity.h"
#include <random>
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
    Keyboard keyboard;

    //Create game instance
    Game game;
    //Bind a keyboard to the game instance
    game.bindKeyboard(&keyboard);
    
    //create a colisor instance
    Colisor colisionPlayerGround;
    //Set the colisor mode to First to all mode
    colisionPlayerGround.setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);

    //Init the window and some other things
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GLOBAL_SCREEN_W, GLOBAL_SCREEN_H, false);

    //Create a player instance
    Player player(game.renderer,"assets/player.png");
    player.bindTypeColision(TypeColision::PLAYER);
    //Bind a colision to the player
    //The player need to be the first 
    colisionPlayerGround.pushNewItem(&player);
    
    //Bind Keyboard to the player
    player.bindKeyboard(&keyboard);
    //Set Player force jump
    player.forceJump = 20;

    //bind a function to the colisor
    colisionPlayerGround.setMethodToColide(ColisionRect);

    //Create some grounds
    const unsigned short lGround = 15;
    LessEntity ground[lGround];
    int positionX = 0;
    //define some grounds
    for (int i = 0; i < lGround; i++) {

        ground[i] = LessEntity(game.renderer,"assets/ground.png");
        ground[i].sprite->box.x = positionX;
        //ground[i].sprite->box.y -= std::rand() % 10;
        game.PushIntoArrayDraw(&ground[i]);
        colisionPlayerGround.pushNewItem(&ground[i]);
        ground[i].bindTypeColision(TypeColision::GROUND);
        positionX += ground[i].boxInfo().w;

    }
    
    //Colision for walls
    Colisor colisionPlayerWall;
    colisionPlayerWall.setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);
    colisionPlayerWall.setMethodToColide(ColisionRect);
    colisionPlayerWall.pushNewItem(&player);

    //Create some walls
    const unsigned short lWall = 1;
    LessEntity wall[lWall];
    positionX = 0;
    for (int i = 0; i < lWall; i++) {

        wall[i] = LessEntity(game.renderer, "assets/wall.png");
        wall[i].sprite->box.x = GLOBAL_SCREEN_W / 2; //- wall[i].objBox.w;
        wall[i].sprite->box.y = GLOBAL_SCREEN_H / 2;  //positionX;
        game.PushIntoArrayDraw(&wall[i]);
        colisionPlayerWall.pushNewItem(&wall[i]);
        wall[i].bindTypeColision(TypeColision::WALL);
        positionX += wall[i].sprite->box.h;
    }

    //Push the player into the game loop
    game.PushIntoArrayDrawUpdate(&player);

    game.PushColisor(&colisionPlayerGround);
    game.PushColisor(&colisionPlayerWall);
    //Init game loop
    game.initLoop();
    return 0;
}
