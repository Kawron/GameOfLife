#include <iostream>
#include <SDL.h>
#include "CellMap.h"
#include "Cell.h"
#include "Vector2d.h"

#define TICK_CHANGE 10
#define INIT_TICK_RATE 100
#define LIVE_COLOR 0x00FFD700
#define DEAD_COLOR 0x002A364A


SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Renderer *gameRenderer = NULL;

int cellMapWidth = 50;
int cellMapHeight = 50;

int cellSize = 25;

int screenWidth = cellMapWidth*cellSize;
int screenHeight = cellMapHeight*cellSize;

void drawCell(int x, int y, unsigned int color) {
    int* pixel = (int*) surface->pixels + ((x*cellSize) + (y*cellSize)*screenWidth);

    for (int n = 0; n < cellSize; n++) {
        for (int m = 0; m < cellSize; m++) {
            *(pixel + (n*screenWidth) + m) = color;
        }
    }
}

void drawMap(CellMap cellMap) {
    for (int i = 0; i < cellMapHeight; i++) {
        for (int j = 0; j < cellMapWidth; j++) {
            Cell *cell = cellMap.getCellAt(Vector2d(j, i));
            if (!cell->getState()) {
                drawCell(j, i, DEAD_COLOR);
            }
            else {
                drawCell(j, i, LIVE_COLOR);
            }
        }
    }
}

void makeCellAlive(CellMap cellMap, int mouseX, int mouseY) {
    std::cout << "mouseX " << mouseX << "mouseY " << mouseY << "\n";
    int x = mouseX / cellSize;
    int y = mouseY / cellSize;
    cellMap.changeCell(x, y);
}

int main() {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    window = SDL_CreateWindow("Game of life",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       screenWidth, screenHeight, 0);
    surface = SDL_GetWindowSurface(window);

    CellMap cellMap = CellMap(cellMapWidth, cellMapHeight);
    cellMap.initialize();

    SDL_Event event;
    int tick_rate = INIT_TICK_RATE;
    bool running = true;
    bool paused = false;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            paused = !paused;
                            break;
                        case SDLK_UP:
                            if (tick_rate - TICK_CHANGE > 0)
                            tick_rate = tick_rate - TICK_CHANGE;
                            break;
                        case SDLK_DOWN:
                            tick_rate = tick_rate + TICK_CHANGE;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    makeCellAlive(cellMap, mouseX, mouseY);
                    drawMap(cellMap);
                    SDL_UpdateWindowSurface(window);
                    break;
            }
        }
        if (!paused) {
            std::cout << tick_rate << "\n";
            drawMap(cellMap);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(tick_rate);
            cellMap.generateNextGeneration();
        }
    }
}
