#pragma once

#include <Python.h>
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
#include <string>
#include <fstream>
using namespace std;

class Game {

public:
	Window* window;
	int isRunning;
	KeyboardHandler* keyboardHandler;

	Player* player;

	Map* map;

	Prize* prize;

	int score = 0;

	
	void init() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = new Window();
		window->init_window("DEMO", 640, 480);
		
		keyboardHandler = new KeyboardHandler();
		Py_Initialize();

		PyObject* pName = PyUnicode_FromString("xmlp");
		PyObject* pModule = PyImport_Import(pName);

		cout << "xmlp imported..." << pModule << endl;

		PyObject* pParseXmlFunc = PyObject_GetAttrString(pModule, "parse_xml");
		PyObject* pParseXmlArgs = PyTuple_Pack(1, Py_BuildValue("s", "map.xml"));

		PyObject* pRoot = PyObject_CallObject(pParseXmlFunc, pParseXmlArgs);


		PyObject* pGetCharacterFunc = PyObject_GetAttrString(pModule, "get_character_atts");
		PyObject* pGetCharacterArgs = PyTuple_Pack(1, pRoot);
		PyObject* pCharacterAttributes = PyObject_CallObject(pGetCharacterFunc, pGetCharacterArgs);
		Py_ssize_t listSize = PyList_Size(pCharacterAttributes);
		vector<int> character_att_lst;
		for (Py_ssize_t i = 0; i < listSize; i++) {
			PyObject* pListItem = PyList_GetItem(pCharacterAttributes, i);
			int item = (int)PyLong_AsLong(pListItem);
			cout << item << endl;
			character_att_lst.push_back(item);
		}

		player = new Player(window->screenSurface, character_att_lst[0], character_att_lst[1], character_att_lst[2], character_att_lst[3]);
		player->setKeyboardHandler(keyboardHandler);
		player->setColor(255, 255, 0);

		map = new Map();
		map->init(window->screenSurface);

		prize = new Prize(window->screenSurface, 0, 0, 30, 30);


		Py_Finalize();

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

		prize->update(dt);

		for (Block* i : map->blockList) {

			i->update(dt);
			collissionCheck(player, i, [&]() {player->blockCollission(i, dt); });

			for (BouncingObstacle* j : map->bouncingObstacleList) {
				collissionCheck(j, i, [&]() {j->blockCollission(i, dt); });
			}
		}

		for (BoundaryObstacle* i : map->boundaryObstacleList) {
			collissionCheck(player, i, [&]() {player->obstacleCollission(i, dt);cout << "Collision!!" << endl;this->isRunning = 0;  highScoreHandler();});

			i->update(dt);
		}

		for (BouncingObstacle* i : map->bouncingObstacleList) {
			collissionCheck(player, i, [&]() {player->obstacleCollission(i, dt); this->isRunning = 0; highScoreHandler(); });
			i->update(dt);
		}
		
		collissionCheck(prize, player, [&]() {prize->playerCollission(dt); score++; window->setWindowTitle(std::to_string(score).c_str()); });
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

		for (BoundaryObstacle* i : map->boundaryObstacleList) {
			i->draw();
		}

		for (BouncingObstacle* i : map->bouncingObstacleList) {
			i->draw();
		}
		
		player->draw();

		prize->draw();

		window->windowRenderEnd();
	}

	void clean() {
		window->destroyWindow();

		SDL_Quit();

	}

	void highScoreHandler() {
		string filePath = "highscore.txt";
		ifstream inputFile(filePath);
		int curHighScore = 0;
		if (inputFile >> curHighScore)
		{
			// File exists
			ofstream outputFile(filePath);
			cout << "Found File" << endl;
			outputFile << max(score, curHighScore);
			outputFile.close();
		}
		else {
			ofstream outputFile(filePath);
			cout << "No File but writing" << endl;
			outputFile << score;
			outputFile.close();
		}
		inputFile.close();
		
		}


};


