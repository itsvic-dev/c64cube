#include <stdio.h>
#include "point.h"
#include "fixedmath.h"

#define PRINT_POINT(str, p) \
    printf(str ": %d/%d/%d\n", (int)p.x, (int)p.y, (int)p.z)

#define PRINT_RAW_FIXED(str, f) \
    printf(str ": %lld\n", f.raw())

int main() {
    puts("[!] MATH TEST");

    Point p0(25, 25, 25);
    PRINT_POINT("P0 BEFORE ROT", p0);

    Fixed angle = rad(45);
    Matrix3x3 rotY = {
        { fxcos(angle), 0, fxsin(angle)},
        {0, 1, 0},
        {-fxsin(angle), 0, fxcos(angle)},
    };

    p0.applyRotMatrix(rotY);
    PRINT_POINT("P0 AFTER ROT", p0);
}
