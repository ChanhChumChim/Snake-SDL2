#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Utilities.h"
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Snake";

struct Box {
    int x;
    int y;
    int size = 10;
    int stepX = 0;
    int stepY = 0;

    void render(SDL_Renderer* renderer) {
        SDL_Rect filled_rect;
        filled_rect.x = x;
        filled_rect.y = y;
        filled_rect.w = size;
        filled_rect.h = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &filled_rect);
    }

    void move() {
        x += stepX;
        y += stepY;
    }

    void turnLeft() {
        stepX = -5;
        stepY = 0;
    }

    void turnRight() {
        stepX = 5;
        stepY = 0;
    }

    void turnDown() {
        stepY = 5;
        stepX = 0;
    }

    void turnUp() {
        stepY = -5;
        stepX = 0;
    }

    bool inside(int minX, int minY, int maxX, int maxY) {
        return (minX <= x && minY <= y && x + size <= maxX && y + size <= maxY);
    }
};

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Texture* background = loadTexture("Background.png", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    SDL_RenderPresent(renderer);

    

    Box box;
    box.x = 10;
    box.y = 10;

    SDL_Event e;

    while (box.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        box.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        box.render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(10);

        if (SDL_PollEvent(&e) == 0) continue;

        if (e.type == SDL_QUIT) break;

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT: box.turnLeft();  break;
            case SDLK_RIGHT: box.turnRight(); break;
            case SDLK_DOWN: box.turnDown(); break;
            case SDLK_UP: box.turnUp(); break;
            default: break;
            }
        }
    }

    quitSDL(window, renderer);
    return 0;
}




