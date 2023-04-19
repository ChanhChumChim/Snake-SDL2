#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Utilities.h"
#include <vector>
#include <algorithm>
#include <deque>
#include <cstdlib>

using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake";

struct Box {
    int x = 10;
    int y = 10;
    int size = 10;
    int stepX = 0;
    int stepY = 0;
    int xa = rand() % 100 * 5 + 0;
    int ya = rand() % 100 * 5 + 0;

    void render1(SDL_Renderer* renderer) {
        SDL_Rect apples;
        apples.x = xa;
        apples.y = ya;
        apples.w = size;
        apples.h = size;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &apples);
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect head;
        head.x = x;
        head.y = y;
        head.w = size;
        head.h = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &head);
    }
    void spawnapple() {
        if (x == xa && y == ya) {
            xa = rand() % 100 * 5 + 0;
            ya = rand() % 100 * 5 + 0;
        }
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

    SDL_Texture* instruction = loadTexture("instruction.png", renderer);
    SDL_RenderCopy(renderer, instruction, NULL, NULL);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();

    Box box;
    
    SDL_Event e;

    while (box.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        box.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);     
        SDL_RenderClear(renderer);
        box.render(renderer);
        box.spawnapple();
        box.render1(renderer);
        SDL_RenderPresent(renderer);

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

    SDL_Texture* background = loadTexture("gameover.png", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();


    SDL_DestroyTexture(background);
    background = NULL;
    SDL_DestroyTexture(instruction);
    instruction = NULL;

    quitSDL(window, renderer);
    return 0;
}




