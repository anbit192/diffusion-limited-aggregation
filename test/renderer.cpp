#include "SDL_render.h"
#include <SDL.h>
#include <iostream>

int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

SDL_Renderer *renderer;
SDL_Window *window;
void pause() {
    std::cout << "Press any key to continue" << std::endl;
    getchar();
}
bool initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << "Failed to initialize SDL :" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool createWindow() {
    window = SDL_CreateWindow("Test", posX, posY, sizeX, sizeY, 0);
    if (window == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }
    return true;
}

bool createRenderer() {
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }
    return true;
}

void setupRenderer() {
    SDL_RenderSetLogicalSize(renderer, sizeX, sizeY);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

bool initEverything() {
    if (!initSDL() || !createWindow() || !createRenderer()) {
        return false;
    }
    setupRenderer();

    return true;
}

void render(SDL_Rect &rect, int delay = 16) {
    for (int i = 0; i < 2000; i++) {

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        rect.x += 10;
        if (rect.x >= posX + sizeX) {
            rect.x = 0;
        }

        SDL_Delay(100);
    }
}

int main() {
    if (!initEverything()) {
        return -1;
    }
    SDL_Rect rect = {20, 20, 10, 10};
    render(rect);
    pause();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
