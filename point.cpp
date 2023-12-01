#include "point.h"

Point::Point()
    : x(0), y(0), z(0) {}

Point::Point(int16_t x, int16_t y)
    : x(x), y(y), z(0) {}

Point::Point(int16_t x, int16_t y, int16_t z)
    : x(x), y(y), z(z) {}

Point::Point(Fixed x, Fixed y, Fixed z)
    : x(x), y(y), z(z) {}

Point Point::operator+(const Point &p1) const {
    return Point(
        x + p1.x,
        y + p1.y,
        z + p1.z
    );
}

void Point::applyRotMatrix(const Matrix3x3 &mat) {
    Fixed ox = x;
    Fixed oy = y;
    Fixed oz = z;

    x = mat[0][0] * ox + mat[0][1] * oy + mat[0][2] * oz;
    y = mat[1][0] * ox + mat[1][1] * oy + mat[1][2] * oz;
    z = mat[2][0] * ox + mat[2][1] * oy + mat[2][2] * oz;
}
