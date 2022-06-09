//
// Created by karol on 30.05.22.
//

#ifndef GAME_OF_LIFE_CELLMAP_H
#define GAME_OF_LIFE_CELLMAP_H

#include "Cell.h"
#include <stdlib.h>
#include <map>
#include <stack>

class CellMap {
public:
    CellMap(int width, int height);
    void initialize();
    void changeCell(int x, int y);
    void generateNextGeneration();
    Cell * getCellAt(Vector2d vec);
private:
    void initNeighbours();
    void updateNeighbours(Cell *cell, bool updateType);
    std::map<Vector2d, Cell*> cells;
    int width;
    int height;
    void acceptCellStates();
    void acceptCellNeighbours();
};


#endif //GAME_OF_LIFE_CELLMAP_H