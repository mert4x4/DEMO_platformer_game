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

    bool canJump = true;
    bool grounded;

    int jumpCounts = 0;
    int maxJumpCount = 2;

    float velocityY;
    float accY;

    void init() {
        this->velocityX = 0;
        this->accX = 0;
        this->targetAccX = 0;
        this->grounded = false;
        this->velocityY = 0;
        this->accY = 0;
        this->canJump = false;
        this->jumpCounts = 0;

        this->x = 100;
        this->y = 100;
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

        if (keyboardHandler->upReleased) {
            this->canJump = true;
        }

        if (keyboardHandler->upPressed && this->canJump && this->jumpCounts > 0) {
            this->canJump = false;
            this->velocityY = -650;
            this->grounded = false;
            this->jumpCounts -= 1;
        }

        this->velocityX += this->targetAccX;
        this->maxSpeedX = 600;

        if (this->velocityX >= this->maxSpeedX)
            this->velocityX = this->maxSpeedX;
        if (this->velocityX <= -this->maxSpeedX)
            this->velocityX = -this->maxSpeedX;


        this->velocityX *= 50 * dt;
        this->y += this->velocityY * dt;
        this->x += this->velocityX * dt;

        if (!this->grounded) {
            this->velocityY += 1500 * dt; //1500 is gravity
        }
        else {
            this->jumpCounts = this->maxJumpCount;
        }

        this->grounded = false;
        rect = { (int)x, (int)y, w, h };
    }

    void obstacleCollission(auto obstacle, auto dt) {
        this->init();
        cout << "Player died..." << endl;
    }

    void blockCollission(auto block, auto dt) {
        bool objectOnBlock = false;
        float overlapX = std::min(this->x + this->w, block->x + block->w) - std::max(this->x, block->x);
        float overlapY = std::min(this->y + this->h, block->y + block->h) - std::max(this->y, block->y);

        if (overlapX > overlapY) {
            if (this->y < block->y) {
                // top collission
                this->grounded = true;
                objectOnBlock = true;
                this->velocityY = 0;
                this->y = block->y - this->h;
            }
            else {
                // bottom collission
                this->velocityY = 0;
                this->grounded = false;
                objectOnBlock = false;
                this->accY = 0;
                this->y = block->y + block->h + 2;
            }
        }
        else {
            if (this->x < block->x) {
                this->velocityX = 0;
                this->x = block->x - this->w;
            }
            else {
                this->velocityX = 0;
                this->x = block->x + block->w;
            }
        }

        if (objectOnBlock) {
            this->grounded = true;
        }
        else {
            this->grounded = false;
        }
        rect = { (int)x, (int)y, w, h };
    }

	
};

