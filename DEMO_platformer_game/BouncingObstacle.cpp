#pragma once

#include <SDL.h>
#include "Entity.cpp"

class BouncingObstacle : public Entity {

public:

    float hspeed;
    float vspeed;


    BouncingObstacle(SDL_Surface* screenSurface, float x, float y, int w, int h, float hspeed, float vspeed)
        : Entity(screenSurface, x, y, w, h), hspeed(hspeed), vspeed(vspeed) {
        setColor(255, 79, 12);
    }


    void update(float dt) {
        this->x += this->hspeed * dt;
        this->y += this->vspeed * dt;

        rect = { (int)x, (int)y, w, h };
    }

    void blockCollission(auto block1, auto dt) {
            float overlapX = min(this->x + this->w, block1->x + block1->w) - max(this->x, block1->x);
            float overlapY = min(this->y + this->h, block1->y + block1->h) - max(this->y, block1->y);

            if (overlapX >= overlapY) {
                // Horizontal collision
                this->vspeed *= -1;
                this->y += vspeed * dt;

            }
            else if (overlapX < overlapY) {
                // Vertical collision
                this->hspeed *= -1;
                this->x += hspeed * dt;
            }

        rect = { (int)x, (int)y, w, h };
    }


};
