#pragma once

#include "Window.cpp"
#include <iostream>
#include <SDL.h>
#include "KeyboardHandler.cpp"
#include "Entity.cpp"
#include "Player.cpp"
#include "Block.cpp"
#include "Map.cpp"
#include "BouncingObstacle.cpp"
#include "Prize.cpp"
#include "BoundaryObstacle.cpp"

using namespace std;

class Game {

public:
	Window* window;
	int isRunning;
	KeyboardHandler* keyboardHandler;

	Player* player;

	BouncingObstacle* obs;

	Map* map;

	Prize* prize;

	BoundaryObstacle* obs2;

	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = new Window();
		window->init_window("asdasdaasda", 640, 480);
		
		keyboardHandler = new KeyboardHandler();

		player = new Player(window->screenSurface, 40, 100, 40, 40);
		player->setKeyboardHandler(keyboardHandler);
		player->setColor(255, 255, 0);

		obs = new BouncingObstacle(window->screenSurface, 40, 100, 20, 20,100,100);

		map = new Map();
		map->init(window->screenSurface);

		prize = new Prize(window->screenSurface, 0, 0, 30, 30);

		obs2 = new BoundaryObstacle(window->screenSurface, 400, 400, 30, 30, 100, 0, 500, 400);


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

		obs->update(dt);

		prize->update(dt);

		obs2->update(dt);

		for (Block* i : map->blockList) {
			i->update(dt);
			collissionCheck(player, i, [&]() {player->blockCollission(i, dt); });
			collissionCheck(obs, i, [&]() {obs->blockCollission(i, dt); });
		}

		collissionCheck(player, obs, [&]() {player->obstacleCollission(obs, dt); });
		collissionCheck(player, obs2, [&]() {player->obstacleCollission(obs2, dt); });

		collissionCheck(prize, player, [&]() {prize->playerCollission(dt); });
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
		
		for (Block* i : map->blockList) {
			i->draw();
		}

		player->draw();

		obs->draw();

		prize->draw();

		obs2->draw();

		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

};