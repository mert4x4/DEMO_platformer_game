#include <SDL.h>
#include <iostream>

class Window {

private:
	SDL_Window* win;

public:
	SDL_Surface* screenSurface;

	int init_window(const char* title, int h, int w) {

		win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, h, w, SDL_WINDOW_SHOWN);
		screenSurface = SDL_GetWindowSurface(win);

		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 255, 255));

		std::cout << "window created!!" << std::endl;

		return 1;
	}

	void windowRenderBegin() {
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 255, 255));
	}

	void windowRenderEnd() {
		SDL_UpdateWindowSurface(win);
	}

	int destroyWindow() {
		SDL_DestroyWindow(win);

		return 0;
	}

	void setWindowTitle(const char* title) {
		SDL_SetWindowTitle(this->win,title);
	}
};
