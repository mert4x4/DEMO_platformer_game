#include <iostream>
#include <SDL.h>
#include "Game.cpp"

const int TARGET_FPS = 60;
const int TARGET_FRAME_TIME = 1000 / TARGET_FPS;

int main(int argc, char* argv[]) {
    Game* game = new Game();
    game->init();

    Uint32 prevTime = SDL_GetTicks();
    Uint32 lagTime = 0;

    while (game->isRunning) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - prevTime;
        prevTime = currentTime;
        lagTime += elapsedTime;

        game->eventHandler();
        game->draw();


        while (lagTime >= TARGET_FRAME_TIME) {
            game->gameLoop(1.0f / TARGET_FPS);
            lagTime -= TARGET_FRAME_TIME;
        }
        game->draw();

    }

    game->clean();
    delete game;

    return 0;
}
