#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

class WelcomeWindow {

private:
    SDL_Surface* screenSurface;
    SDL_Rect startButton;
    SDL_Rect endButton;
    SDL_Rect highScoreField;
public:
    
    WelcomeWindow(SDL_Surface* screenSurface, int screenWidth, int screenHeight) : screenSurface(screenSurface){
        startButton = { screenWidth / 4 - 25, 3* screenHeight / 8, 200, 50 };
        endButton = {  2* screenWidth / 4 + 25, 3* screenHeight / 8, 200, 50 }; // Adjusted position
        highScoreField = { 3*screenWidth / 8, 100 + 3* screenHeight / 8, 200, 50 };
    }

    void init() {
    }
    
    void draw() {
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 128)); // Pink color
        SDL_FillRect(screenSurface, &startButton, SDL_MapRGB(screenSurface->format, 0, 255, 0)); // Start Button
        SDL_FillRect(screenSurface, &endButton, SDL_MapRGB(screenSurface->format, 255, 0, 0));   // End Button
        SDL_FillRect(screenSurface, &highScoreField, SDL_MapRGB(screenSurface->format, 255, 255, 255));   // High Score
     }

    void handleEvent(SDL_Event& event, bool& startGame, bool& quitGame) {
        // Handle events related to the welcome page
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (isStartButtonClicked(mouseX, mouseY)) {
                    std::cout << "Start button clicked!" << std::endl;
                    startGame = true;
                }
                else if (isEndButtonClicked(mouseX, mouseY)) {
                    std::cout << "End button clicked!" << std::endl;
                    quitGame = true;
                }

            }
            break;
        }
    }

    bool isEndButtonClicked(int mouseX, int mouseY) {
        return (mouseX >= endButton.x && mouseX <= endButton.x + endButton.w &&
            mouseY >= endButton.y && mouseY <= endButton.y + endButton.h);
    }

    bool isStartButtonClicked(int mouseX, int mouseY) {
        return (mouseX >= startButton.x && mouseX <= startButton.x + startButton.w &&
            mouseY >= startButton.y && mouseY <= startButton.y + startButton.h);
    }

    ~WelcomeWindow() {
    }

};
