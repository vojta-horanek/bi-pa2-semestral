#ifndef TPOHB_VEC_H
#define TPOHB_VEC_H

#include <cmath>

struct Vec {
    int x = 0;
    int y = 0;

    Vec(int x, int y) : x(x), y(y) {}

    Vec operator+(const Vec &other) const {
        return {this->x + other.x, this->y + other.y};
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
        return sqrt(a*a + b*b);
    }
};


#endif //TPOHB_VEC_H
