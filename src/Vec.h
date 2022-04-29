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

    Vec operator+(const Vec &other) const {
        return {this->x + other.x, this->y + other.y};
    }

    Vec &operator+=(const Vec &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vec operator-(const Vec &other) const {
        return {this->x - other.x, this->y - other.y};
    }

    Vec operator+(int other) const {
        return {this->x + other, this->y + other};
    }

    Vec operator-(int other) const {
        return *this + (-other);
    }

    Vec operator*(int other) const {
        return {this->x * other, this->y * other};
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
};


#endif //TPOHB_VEC_H
