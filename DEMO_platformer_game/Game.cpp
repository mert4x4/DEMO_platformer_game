#include "Window.cpp"
#include <iostream>
#include <SDL.h>
#include "KeyboardHandler.cpp"
#include "Entity.cpp"
#include "Player.cpp"
#include "Block.cpp"


using namespace std;

class Game {

public:
	Window* window;
	int isRunning;
	KeyboardHandler* keyboardHandler;

	Player* player;
	Block* block;

	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = new Window();
		window->init_window("asdasdaasda", 640, 480);
		

		keyboardHandler = new KeyboardHandler();

		block = new Block(window->screenSurface,40,40,40,40);

		player = new Player(window->screenSurface, 40, 40, 40, 40);
		player->setKeyboardHandler(keyboardHandler);
		player->setColor(255, 255, 0);

		this->isRunning = 1;
	}

	void eventHandler() {
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			isRunning = 0;
			break;
		default:
			break;
		}
		keyboardHandler->handleKeyboard(event);

	}

	void gameLoop(float dt) {
		

		player->update(dt);
		block->update(dt);
		collissionCheck(player, block, [&]() {player->blockCollission(); });

	}

	auto collissionCheck(auto e1, auto e2, auto function) {
		float left1 = e1->x;
		float right1 = e1->x + e1->w;
		float top1 = e1->y;
		float bottom1 = e1->y + e1->h;

		float left2 = e2->x;
		float right2 = e2->x + e2->w;
		float top2 = e2->y;
		float bottom2 = e2->y + e2->h;

		if (right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2) {
			return;
		}
		function();
	}


	void draw() {
		window->windowRenderBegin();
		
		block->draw();
		player->draw();

		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

};