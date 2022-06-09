//
// Created by karol on 30.05.22.
//

#ifndef GAME_OF_LIFE_VECTOR2D_H
#define GAME_OF_LIFE_VECTOR2D_H


#include <cstddef>
#include <functional>

class Vector2d {
public:
    Vector2d(int x, int y);
    int getX() const;
    int getY() const;

    size_t operator()(const Vector2d& p) const
    {
        return (std::hash<int>()(p.x)) ^
               (std::hash<int>()(p.y));
    }

    bool operator==(const Vector2d &rhs) const;

    bool operator!=(const Vector2d &rhs) const;

    bool operator<(const Vector2d &rhs) const;

    bool operator>(const Vector2d &rhs) const;

    bool operator<=(const Vector2d &rhs) const;

    bool operator>=(const Vector2d &rhs) const;

private:
    int x;
    int y;
};

#endif //GAME_OF_LIFE_VECTOR2D_H
