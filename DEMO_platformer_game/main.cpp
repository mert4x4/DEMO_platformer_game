#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Game.cpp"
#include "WelcomeWindow.cpp"
using namespace std;

const int TARGET_FPS = 60;
const int TARGET_FRAME_TIME = 1000 / TARGET_FPS;

int main(int argc, char* argv[]) {
SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* welcomeWindowSDL = SDL_CreateWindow("Welcome", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Surface* welcomeScreenSurface = SDL_GetWindowSurface(welcomeWindowSDL);

    WelcomeWindow* welcomeWindow = new WelcomeWindow(welcomeScreenSurface, 800, 600);

    // strýng state  "Wlcome"
   //ýf play state  = Ýgame"
    SDL_Event welcomeEvent;
    bool welcomeRunning = true;
    bool startGame = false;
    bool quitGame = false;

    while (welcomeRunning && !startGame && !quitGame) {
        while (SDL_PollEvent(&welcomeEvent) != 0) {
            if (welcomeEvent.type == SDL_QUIT) {
                welcomeRunning = false;
            }
            welcomeWindow->handleEvent(welcomeEvent, startGame, quitGame);
        }
        
        welcomeWindow->draw();
        SDL_UpdateWindowSurface(welcomeWindowSDL);
    }
    
    if (startGame) {
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
        }

        game->clean();
        delete game;
    }

    SDL_DestroyWindow(welcomeWindowSDL);

    return 0;
}
