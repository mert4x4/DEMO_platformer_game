#include "Window.cpp"
#include <iostream>
#include <SDL.h>
#include "KeyboardHandler.cpp"
#include "Entity.cpp"

using namespace std;

class Game {

public:
	Window* window;
	int isRunning;
	KeyboardHandler* keyboardHandler;

	Entity* deneme;

	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = new Window();
		window->init_window("asdasdaasda", 640, 480);
		

		keyboardHandler = new KeyboardHandler();

		deneme = new Entity(window->screenSurface,40,40,40,40);


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

		if (keyboardHandler->leftPressed) {
			deneme->x -= 200 * dt;
			cout << deneme->x << endl;

		}
			
		if (keyboardHandler->rightPressed)
			deneme->x += 200 * dt;

		deneme->update(dt);
	}

	void draw() {
		window->windowRenderBegin();
		deneme->draw();

		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

};