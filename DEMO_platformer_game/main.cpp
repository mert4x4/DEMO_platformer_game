#include <iostream>
#include <SDL.h>
#include "Game.cpp"
#include <cassert>
using namespace std;

const int TARGET_FPS = 60;
const int TARGET_FRAME_TIME = 1000 / TARGET_FPS;

int main(int argc, char* argv[]) {
    Game* game = new Game();
    game->init();
    SDL_Surface* dummyScreenSurface = nullptr;  // Replace with a valid surface if needed
    KeyboardHandler* keyboardHandler;
    // Test Player Constructor
    Player player(nullptr, 10.0f, 20.0f, 30, 40);
   
   

    //Tests
    //first state
    assert(player.velocityX == 0);
    assert(player.velocityY == 0);
    assert(player.accX == 0);
    assert(player.accY == 0);
    assert(player.targetAccX == 0);
    assert(player.maxSpeedX == 0);
    assert(player.canJump == true);
    assert(player.grounded == false);
    assert(player.jumpCounts == 0);
    assert(player.maxJumpCount == 2);
    assert(player.x == 10.0f);
    assert(player.y == 20.0f);
    assert(game->getPlayer() != nullptr);
    
    
    
    
    
   // player.update(0.1f);
    Block* testBlock = new Block(game->window->screenSurface, 50, 50, 20, 20);
    player.blockCollission(testBlock, 0.1f);
    
    
    BouncingObstacle* testObstacle = new BouncingObstacle(game->window->screenSurface, 60, 60, 20, 20, 5.0f, 5.0f);
    player.obstacleCollission(testObstacle, 0.1f);

    Prize* testPrize = new Prize(game->window->screenSurface, 200, 200, 20, 20);
    // Ensure the prize is created
    assert(testPrize != nullptr);
    delete testPrize;
    delete testBlock;
    delete testObstacle;
  

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
        //cout << game->isRunning << endl;
    }

    game->clean();
    delete game;

    return 0;
}
