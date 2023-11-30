#pragma once
#include <stdint.h>

class Point {
public:
    Point(uint16_t x, uint16_t y);
    Point(uint16_t x, uint16_t y, uint16_t z);

    uint16_t x;
    uint16_t y;
    uint16_t z;

    Point operator+(const Point &p1) const;
};
