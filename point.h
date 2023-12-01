#pragma once
#include <stdint.h>
#include "fixed.h"

typedef Fixed Matrix3x3[3][3];

class Point {
public:
    Point(int16_t x, int16_t y);
    Point(int16_t x, int16_t y, int16_t z);
    Point(Fixed x, Fixed y, Fixed z);

    Fixed x;
    Fixed y;
    Fixed z;

    Point operator+(const Point &p1) const;

    void applyRotMatrix(const Matrix3x3 &mat);
};
