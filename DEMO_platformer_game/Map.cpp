#pragma once

#include <iostream>
#include <list>
#include "Block.cpp"
#include "BoundaryObstacle.cpp"
#include "BouncingObstacle.cpp"


using namespace std;

class Map {
public:

    Block* wall1;
    Block* wall2;
    Block* wall3;
    Block* wall4;

    Block* block1_;
    Block* block2_;
    Block* block4_;

    list<Block*> blockList;

    BouncingObstacle* obs1;
    list<BouncingObstacle*> bouncingObstacleList;


    BoundaryObstacle* obs2;
    list<BoundaryObstacle*> boundaryObstacleList;

    void init(SDL_Surface* screenSurface) {
        blockList = list<Block*>();


        block1_ = new Block(screenSurface, 450, 300, 100, 80);
        block2_ = new Block(screenSurface, 240, 250, 100, 80);

        block4_ = new Block(screenSurface, 100, 410, 60, 30);

        wall1 = new Block(screenSurface, 0, 0, 640, 10); //top
        wall2 = new Block(screenSurface, 0, 0, 10, 480); //left
        wall3 = new Block(screenSurface, 630, 0, 10, 480); //right
        wall4 = new Block(screenSurface, 0, 470, 640, 10); //bottom

        blockList.push_back(block1_);
        blockList.push_back(block2_);
        blockList.push_back(block4_);

        blockList.push_back(wall1);
        blockList.push_back(wall2);
        blockList.push_back(wall3);
        blockList.push_back(wall4);

        ////////////////////////////////////////////////////////////////////

        bouncingObstacleList = list<BouncingObstacle*>();
        obs1 = new BouncingObstacle(screenSurface, 40, 100, 20, 20, 100, 100);
        bouncingObstacleList.push_back(obs1);

        /////////////////////////////////////////////////////////////////////

        boundaryObstacleList = list<BoundaryObstacle*>();
        obs2 = new BoundaryObstacle(screenSurface, 400, 400, 30, 30, 100, 0, 500, 400);
        boundaryObstacleList.push_back(obs2);

        cout << "map initied..." << endl;
    }




};