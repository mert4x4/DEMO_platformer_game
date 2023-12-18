#include "Window.cpp"
#include <iostream>
#include <SDL.h>
#include "KeyboardHandler.cpp"
#include "Entity.cpp"
#include "Player.cpp"

using namespace std;

class Game {

public:
	Window* window;
	int isRunning;
	KeyboardHandler* keyboardHandler;

	Entity* deneme;
	Player* player;

	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = new Window();
		window->init_window("asdasdaasda", 640, 480);
		

		keyboardHandler = new KeyboardHandler();

		deneme = new Entity(window->screenSurface,40,40,40,40);
		player = new Player(window->screenSurface, 40, 40, 40, 40);


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
		
		if (keyboardHandler->rightPressed && keyboardHandler->leftPressed) {
			player->targetAccX = 0;
		}
		else if (keyboardHandler->rightPressed) {
			player->targetAccX = 100.0f;
		}
		else if (keyboardHandler->leftPressed) {
			player->targetAccX = -100.0f;
		}
		else {
			player->targetAccX = 0;
		}

		player->velocityX += player->targetAccX;
		player->maxSpeedX = 600;

		if (player->velocityX >= player->maxSpeedX)
			player->velocityX = player->maxSpeedX;
		if (player->velocityX <= -player->maxSpeedX)
			player->velocityX = -player->maxSpeedX;
		
		player->velocityX *= 50 * dt;
		player->x += player->velocityX * dt;
		player->update(dt);
	}

	void draw() {
		window->windowRenderBegin();
		
		deneme->draw();
		player->draw();


		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

};