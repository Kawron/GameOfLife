//
// Created by karol on 30.05.22.
//

#include "Vector2d.h"

Vector2d::Vector2d(int x, int y) : x(x), y(y) {}

int Vector2d::getX() const {
    return x;
}

int Vector2d::getY() const {
    return y;
}

bool Vector2d::operator==(const Vector2d &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Vector2d::operator!=(const Vector2d &rhs) const {
    return !(rhs == *this);
}

bool Vector2d::operator<(const Vector2d &rhs) const {
    if (x < rhs.x)
        return true;
    if (rhs.x < x)
        return false;
    return y < rhs.y;
}

bool Vector2d::operator>(const Vector2d &rhs) const {
    return rhs < *this;
}

bool Vector2d::operator<=(const Vector2d &rhs) const {
    return !(rhs < *this);
}

bool Vector2d::operator>=(const Vector2d &rhs) const {
    return !(*this < rhs);
}
