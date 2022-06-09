//
// Created by karol on 30.05.22.
//

#include "CellMap.h"
#include "Cell.h"
#include <iostream>

CellMap::CellMap(int width, int height) : width(width), height(height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Vector2d vec = Vector2d(i, j);

            Cell *cell = new Cell(vec);
            this->cells.insert({vec, cell});
        }
    }
}

// will create random pattern for now
void CellMap::initialize() {
    this->cells.at(Vector2d(5,3))->setState(true);
    this->cells.at(Vector2d(6,3))->setState(true);
    this->cells.at(Vector2d(7,3))->setState(true);
    this->acceptCellStates();
    this->initNeighbours();
    this->acceptCellNeighbours();
}

// generating new iteration, will update nieghbours and states
void CellMap::generateNextGeneration() {
    for (auto const& pair : cells) {
        Cell *cell = pair.second;
        if (cell->getState() == 0 && cell->getAliveNeighbours() == 3) {
            cell->setState(true);
            // update all neighbours
            updateNeighbours(cell, true);
        }
        if (cell->getState() == 1) {
            int aliveNeigh = cell->getAliveNeighbours();
            if (aliveNeigh != 2 && aliveNeigh != 3) {
                cell->setState(false);
                // update all neighbours
                updateNeighbours(cell, false);
            }
        }
    }
    acceptCellStates();
    acceptCellNeighbours();
}

void CellMap::updateNeighbours(Cell *cell, bool updateType) {
    int x = cell->getX();
    int y = cell->getY();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int new_x = x + i;
            int new_y = y + j;
            if (!updateType) {
                // decrement
                if (this->cells.find(Vector2d(new_x,new_y)) != this->cells.end()) {
                    this->cells.at(Vector2d(new_x,new_y))->changeNeighbour(-1);
                }
            }
            else {
                //increment
                if (this->cells.find(Vector2d(new_x,new_y)) != this->cells.end()) {
                    this->cells.at(Vector2d(new_x,new_y))->changeNeighbour(1);
                }
            }
        }
    }
}

Cell* CellMap::getCellAt(Vector2d vec) {
    Cell *cell = this->cells.at(vec);
    return cell;
}

void CellMap::acceptCellStates() {
    for (auto const& pair : cells) {
        pair.second->acceptState();
    }
}

void CellMap::initNeighbours() {
    for (auto const& pair : cells) {
        Cell *cell = pair.second;
        int x = cell->getX();
        int y = cell->getY();
        int cnt = 0;
        for (int n = -1; n <= 1; n++) {
            for (int m = -1; m <= 1; m++) {
                if (n == 0 && m == 0) {
                    continue;
                }
                if (this->cells.find(Vector2d(x+m,y+n)) != this->cells.end()) {
                    Cell *neighbour = this->getCellAt(Vector2d(x+m,y+n));
                    if (neighbour->getState()) {
                        cnt++;
                    }
                }
            }
        }
        cell->changeNeighbour(cnt);
    }
}

void CellMap::acceptCellNeighbours() {
    for (auto const& pair : cells) {
        pair.second->acceptNeighbour();
    }
}

void CellMap::changeCell(int x, int y) {
    Vector2d vec = Vector2d(x, y);
    std::cout << "changeCell x " << x << "y " << y << "\n";
    Cell *cell = getCellAt(vec);
    cell->setState(true);
    this->updateNeighbours(cell, true);
    this->acceptCellStates();
    this->acceptCellNeighbours();
}


