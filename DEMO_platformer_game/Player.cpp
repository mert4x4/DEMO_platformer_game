#pragma once

#include <SDL.h>
#include <iostream>
#include "Entity.cpp"
using namespace std;


class Player : public Entity {

public:
    using Entity::Entity;

    float velocityX;
    float accX;
    float targetAccX;
    float maxSpeedX;

    void init() {
        velocityX = 0.0f;
        rect = { (int)x, (int)y, w, h };
        accX = 0;
        targetAccX = 0;
    }










};

