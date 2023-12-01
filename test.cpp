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

    for (int i = 0; i <= 180; i += 45) {
        printf("-- ANGLE: %d\n", i);
        Fixed angle = rad(i);
        Matrix3x3 rotZ = {
            {fxcos(angle), -fxsin(angle), 0},
            {fxsin(angle),  fxcos(angle), 0},
            {0, 0, 1},
        };
        Point p1 = p0;
        p1.applyRotMatrix(rotZ);
        PRINT_POINT("P0 AFTER ROT", p1);
        PRINT_RAW_FIXED("SIN", fxsin(angle));
        PRINT_RAW_FIXED("COS", fxcos(angle));
    }
}
