#include <iostream>
#include "GlobalDefs.h"
#include "Game.h"
#include "Player.h"
#include "LessEntity.h"
#include "Colisor.h"
#include <random>

bool ColisionGround(const SDL_Rect& sub, const SDL_Rect& other) {

    if ((sub.x + sub.w) > other.x &&
        sub.x < (other.x + other.w) &&
        (sub.y + sub.h) > other.y &&
        sub.y < (other.y + other.h))
    {
        return true;
    }

    return false;
}

bool ColisionWall(const SDL_Rect& sub, const SDL_Rect& other) {

    if ((sub.x + sub.w) > other.x &&
        sub.x < (other.x + other.w) &&
        (sub.y + sub.h) > other.y &&
        sub.y < (other.y + other.h)) {
        return true;
    }

    return false;
}

int main(int argc, char* argv[])
{
    //Create keyboard instance
    Keyboard keyboard;

    //Create game instance
    Game game;
    //Bind a keyboard to the game instance
    game.bindKeyboard(&keyboard);
    
    //create a colisor instance
    Colisions::Colisor colisionPlayerGround;
    //Set the colisor mode to First to all mode
    colisionPlayerGround.setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);

    //Init the window and some other things
    game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GLOBAL_SCREEN_W, GLOBAL_SCREEN_H, false);

    //Create a player instance
    Player player(game.renderer);
    player.bindTypeColision(Colisions::Type::PLAYER);
    //Bind a colision to the player
    //The player need to be the first 
    colisionPlayerGround.pushNewItem(&player);
    
    //Bind Keyboard to the player
    player.bindKeyboard(&keyboard);
    //Set Player force jump
    player.forceJump = 20;


    //bind a function to the colisor
    colisionPlayerGround.setMethodToColide(ColisionGround);

    //Create some grounds
    const unsigned short lGround = 15;
    LessEntity ground[lGround];
    int positionX = 0;
    //define some grounds
    for (int i = 0; i < lGround; i++) {

        ground[i] = LessEntity(game.renderer,"assets/ground.png");
        ground[i].objBox.x = positionX;
        ground[i].objBox.y -= std::rand() % 10;
        game.PushIntoArrayDraw(&ground[i]);
        colisionPlayerGround.pushNewItem(&ground[i]);
        ground[i].bindTypeColision(Colisions::Type::GROUND);
        positionX += ground[i].boxInfo().w;

    }
    
    //Colision for walls
    Colisions::Colisor colisionPlayerWall;
    colisionPlayerWall.setModeToColide(COLISOR_FIRST_TO_ALL_MODE_A);
    colisionPlayerWall.setMethodToColide(ColisionWall);
    colisionPlayerWall.pushNewItem(&player);

    //Create some walls
    const unsigned short lWall = 15;
    LessEntity wall[lWall];
    positionX = 0;
    for (int i = 0; i < lWall; i++) {

        wall[i] = LessEntity(game.renderer, "assets/wall.png");
        wall[i].objBox.x = GLOBAL_SCREEN_W - wall[i].objBox.w;
        wall[i].objBox.y = positionX;
        game.PushIntoArrayDraw(&wall[i]);
        colisionPlayerWall.pushNewItem(&wall[i]);
        wall[i].bindTypeColision(Colisions::Type::WALL);
        positionX += wall[i].objBox.h;
    }


    //Push the player into the game loop
    game.PushIntoArrayDrawUpdate(&player);

    /*const unsigned short lWall = 15;
    LessEntity wall[lWall];
    int positionY = 0;
    //Create a Wall in right size
    for (int i = 0; i < lWall; i++) {

    }*/

    game.PushColisor(&colisionPlayerGround);
    game.PushColisor(&colisionPlayerWall);
    //Init game loop
    game.initLoop();
    return 0;
}
