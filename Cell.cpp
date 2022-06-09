//
// Created by karol on 30.05.22.
//

#include <iostream>
#include "Cell.h"

Cell::Cell(const Vector2d &pos) : pos(pos) {
    this->state = 0;
    this->newState = 0;
    this->aliveNeighbours = 0;
    this->futureNeighbours = 0;
}

bool Cell::getState() const {
    return this->state;
}

int Cell::getAliveNeighbours() const {
    return this->aliveNeighbours;
}

int Cell::getX() const {
    return this->pos.getX();
}

int Cell::getY() const {
    return this->pos.getY();
}

void Cell::setState(bool newState) {
    this->newState = newState;
}

void Cell::acceptState() {
    this->state = newState;
}

void Cell::changeNeighbour(int val) {
    this->futureNeighbours += val;
}

void Cell::acceptNeighbour() {
    this->aliveNeighbours += futureNeighbours;
    futureNeighbours = 0;
}