#pragma once

#include <SDL.h>
#include <iostream>
#include "Entity.cpp"
#include "KeyboardHandler.cpp"
using namespace std;


class Player : public Entity {

public:
    using Entity::Entity;

    float velocityX;
    float accX;
    float targetAccX;
    float maxSpeedX;

	KeyboardHandler* keyboardHandler;

    void init() {
        velocityX = 0.0f;
        rect = { (int)x, (int)y, w, h };
        accX = 0;
        targetAccX = 0;
    }


	void setKeyboardHandler(KeyboardHandler* kh) {
		this->keyboardHandler = kh;
	}

    void update(float dt) {
		if (keyboardHandler->rightPressed && keyboardHandler->leftPressed) {
			this->targetAccX = 0;
		}
		else if (keyboardHandler->rightPressed) {
			this->targetAccX = 100.0f;
		}
		else if (keyboardHandler->leftPressed) {
			this->targetAccX = -100.0f;
		}
		else {
			this->targetAccX = 0;
		}

		this->velocityX += this->targetAccX;
		this->maxSpeedX = 600;

		if (this->velocityX >= this->maxSpeedX)
			this->velocityX = this->maxSpeedX;
		if (this->velocityX <= -this->maxSpeedX)
			this->velocityX = -this->maxSpeedX;

		this->velocityX *= 50 * dt;
		this->x += this->velocityX * dt;

		rect = { (int)x, (int)y, w, h };
		cout << "asdasd" << endl;
    }

	void blockCollission() {
		cout << "collided with block..." << endl;
	}
};

