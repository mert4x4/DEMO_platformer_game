#pragma once

#include <SDL.h>
#include "Entity.cpp"

class BoundaryObstacle : public Entity {

public:

    float hspeed;
    float vspeed;

    float endpoint1_x;
    float endpoint1_y;

    float endpoint2_x;
    float endpoint2_y;


    BoundaryObstacle(SDL_Surface* screenSurface, float x, float y, int w, int h, float hspeed, float vspeed, float endpoint_x, float endpoint_y)
        : Entity(screenSurface, x, y, w, h), hspeed(hspeed), vspeed(vspeed), endpoint1_x(x), endpoint1_y(y), endpoint2_x(endpoint_x), endpoint2_y(endpoint_y) {
        setColor(255, 31, 255);
    }



    void update(float dt) {

        this->x += this->hspeed * dt;
        this->y += this->vspeed * dt;

        if (this->x > this->endpoint2_x || this->x < this->endpoint1_x) {
            this->hspeed *= -1;
        }
        if (this->y > this->endpoint2_y || this->y < this->endpoint1_y) {
            this->vspeed *= -1;
        }

        rect = { (int)x, (int)y, w, h };
    }

};








