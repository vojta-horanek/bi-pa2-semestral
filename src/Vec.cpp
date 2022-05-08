#include "Vec.h"
#include <cmath>
#include <ostream>
#include "Constants.h"

Vec::Vec() = default;

Vec::Vec(int x, int y) : x(x), y(y) {}

bool Vec::isOrigin() const {
    return x == 0 && y == 0;
}

Vec Vec::operator+(const Vec &other) const {
    return {this->x + other.x, this->y + other.y};
}

Vec &Vec::operator+=(const Vec &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vec &Vec::operator-=(const Vec &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vec Vec::operator-(const Vec &other) const {
    return {this->x - other.x, this->y - other.y};
}

Vec Vec::operator+(int other) const {
    return {this->x + other, this->y + other};
}

Vec Vec::operator-(int other) const {
    return *this + (-other);
}

Vec Vec::operator*(int other) const {
    return {this->x * other, this->y * other};
}

bool Vec::operator==(const Vec &lhs) const {
    return lhs.x == x && lhs.y == y;
}

bool Vec::operator!=(const Vec &lhs) const {
    return !(*this == lhs);
}

Vec Vec::withX(int addedX) const {
    return {x + addedX, y};
}

Vec Vec::withY(int addedY) const {
    return {x, y + addedY};
}

double Vec::distanceTo(const Vec &other) const {
    int a = abs(other.x - x);
    int b = abs(other.y - y);
    return sqrt(a * a + b * b);
}

Vec Vec::getScaled() const {
    return *this * REAL_PIXEL_SIZE * BLOCK_SIZE;
}

bool Vec::operator<(const Vec &p1) const {
    if (p1.x != x) {
        return x < p1.x;
    } else {
        return y < p1.y;
    }
}

std::ostream &operator<<(std::ostream &s, const Vec &vec) {
    s << "(" << vec.x << ", " << vec.y << ")";
    return s;
}

void Vec::scale() {
    *this = *this * REAL_PIXEL_SIZE * BLOCK_SIZE;
}

int Vec::xDistance(const Vec &other) const {
    return abs(this->x - other.x);
}

int Vec::yDistance(const Vec &other) const {
    return abs(this->y - other.y);
}

Vec Vec::max() {
    return Vec(INT32_MAX, INT32_MAX);
}


