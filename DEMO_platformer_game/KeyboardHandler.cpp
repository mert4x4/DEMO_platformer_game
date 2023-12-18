#pragma once

#include <SDL.h>
#include <iostream>


class KeyboardHandler {

public:
	bool rightPressed;
	bool leftPressed;
	bool upPressed;

	bool upReleased;

	void handleKeyboard(SDL_Event& event) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_d) {
				rightPressed = true;
			}
			if (event.key.keysym.sym == SDLK_a) {
				leftPressed = true;
			}
			if (event.key.keysym.sym == SDLK_w) {
				upPressed = true;
				upReleased = false;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_d) {
				rightPressed = false;
			}
			if (event.key.keysym.sym == SDLK_a) {
				leftPressed = false;
			}
			if (event.key.keysym.sym == SDLK_w) {
				upPressed = false;
				upReleased = true;
			}
			break;
		}
	}
};