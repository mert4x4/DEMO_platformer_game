#pragma once

#include <iostream>
#include <list>
#include "Entity.cpp"

class Prize : public Entity {
public:

    struct Coordinate {
        int x;
        int y;
    };

    list<Coordinate> coordinates;

    Prize(SDL_Surface* screenSurface, float x, float y, int w, int h) : Entity(screenSurface, x, y, w, h) {

        this->coordinates.push_back({ 400, 80 });
        this->coordinates.push_back({ 600, 70 });
        this->coordinates.push_back({ 380, 270 });
        this->coordinates.push_back({ 200, 200 });


        this->setColor(255, 255, 31);

        this->x = coordinates.front().x;
        this->y = coordinates.front().y;


        rect = { (int)x, (int)y, w, h };
    }

    void playerCollission(float dt){
            cout << "score!!" << endl;

            Coordinate temp = coordinates.front();
            coordinates.pop_front();
            coordinates.push_back(temp);

            this->x = coordinates.front().x;
            this->y = coordinates.front().y;
        
        rect = { (int)x, (int)y, w, h };
    }

};