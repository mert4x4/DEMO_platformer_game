#include "Window.cpp"
#include <iostream>
#include <SDL.h>


using namespace std;

class Game {

public:
	Window* window;
	int isRunning;

	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);

		window = new Window();
		window->init_window("asdasdaasda", 640, 480);

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
	}

	void gameLoop(float dt) {



	}

	void draw() {
		window->windowRenderBegin();


		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

};