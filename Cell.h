//
// Created by karol on 30.05.22.
//

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H
#include "Vector2d.h"

class Cell {
public:
    explicit Cell(const Vector2d &pos);

    void setState(bool newState);
    void acceptState();

    void changeNeighbour(int val);
    void acceptNeighbour();

    int getAliveNeighbours() const;
    bool getState() const;
    int getX() const;
    int getY() const;

private:
    Vector2d pos;
    bool newState;
    bool state;
    int futureNeighbours;
    int aliveNeighbours;
};


#endif //GAME_OF_LIFE_CELL_H
