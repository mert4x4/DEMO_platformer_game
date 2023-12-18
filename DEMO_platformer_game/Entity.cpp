#pragma once

#include <SDL.h>
#include "KeyboardHandler.cpp"
#include <iostream>
#include <list>
using namespace std;

class Entity {
public:

    SDL_Surface* screenSurface;
    SDL_Rect rect;

    float x;
    float y;
    int w;
    int h;

    int r = 255;
    int g = 255;
    int b = 255;

    Entity(SDL_Surface* screenSurface, float x, float y, int w, int h) {
        this->screenSurface = screenSurface;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;

        rect = { (int)x, (int)y, w, h };
    }

    void update(float dt) {
        rect = { (int)x, (int)y, w, h };
    }

    void draw() {
        SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, r, g, b));
    }

    void setColor(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};