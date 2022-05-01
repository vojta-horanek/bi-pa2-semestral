#ifndef TPOHB_VEC_H
#define TPOHB_VEC_H

#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"

struct Vec {
    int x = 0;
    int y = 0;

    Vec() = default;

    Vec(int x, int y) : x(x), y(y) {}

    inline bool isOrigin() const {
        return x == 0 && y == 0;
    }

    inline Vec operator+(const Vec &other) const {
        return {this->x + other.x, this->y + other.y};
    }

    inline Vec &operator+=(const Vec &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    inline Vec operator-(const Vec &other) const {
        return {this->x - other.x, this->y - other.y};
    }

    inline Vec operator+(int other) const {
        return {this->x + other, this->y + other};
    }

    inline Vec operator-(int other) const {
        return *this + (-other);
    }

    inline Vec operator*(int other) const {
        return {this->x * other, this->y * other};
    }

    inline bool operator==(const Vec &lhs) const {
        return lhs.x == x && lhs.y == y;
    }

    inline Vec withX(int addedX) const {
        return {x + addedX, y};
    }

    inline Vec withY(int addedY) const {
        return {x, y + addedY};
    }

    // TODO Check correctness
    double distanceTo(const Vec &other) const {
        int a = abs(other.x - x);
        int b = abs(other.y - y);
        return sqrt(a * a + b * b);
    }

    Vec getScaled() const {
        return *this * REAL_PIXEL_SIZE * BLOCK_SIZE;
    }

    SDL_Point point() const {
        return SDL_Point{x, y};
    }


    inline bool operator<(const Vec &p1) const {
        if (p1.x != x) {
            return x < p1.x;
        } else {
            return y < p1.y;
        }
    }
};


#endif //TPOHB_VEC_H
