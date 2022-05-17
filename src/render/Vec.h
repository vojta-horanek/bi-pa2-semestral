#ifndef TPOHB_VEC_H
#define TPOHB_VEC_H

#include <ostream>

struct Vec {
    int x = 0;
    int y = 0;

    Vec();

    Vec(int x, int y);

    static Vec max();

    Vec operator+(const Vec &other) const;

    Vec operator+(int other) const;

    Vec operator-(const Vec &other) const;

    Vec operator-(int other) const;

    Vec &operator+=(const Vec &other);

    Vec &operator-=(const Vec &other);

    Vec operator*(int other) const;

    bool operator==(const Vec &lhs) const;

    bool operator!=(const Vec &lhs) const;

    Vec withX(int addedX) const;

    Vec withY(int addedY) const;

    int xDistance(const Vec &other) const;

    int yDistance(const Vec &other) const;

    Vec getScaled() const;

    bool operator<(const Vec &p1) const;

    friend std::ostream &operator<<(std::ostream &s, const Vec &vec);
};

#endif // TPOHB_VEC_H
