#include "point.h"

Point::Point(uint16_t x, uint16_t y)
    : x(x), y(y), z(0) {}

Point::Point(uint16_t x, uint16_t y, uint16_t z)
    : x(x), y(y), z(z) {}

Point Point::operator+(const Point &p1) const {
    return Point(
        x + p1.x,
        y + p1.y,
        z + p1.z
    );
}
