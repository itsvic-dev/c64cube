#include <stdio.h>
#include "point.h"
#include "fixedmath.h"

#define PRINT_POINT(str, p) \
    printf(str ": %d/%d/%d\n", (int)p.x, (int)p.y, (int)p.z)

int main() {
    puts("[!] MATH TEST");

    Point p0(25, 25, 25);
    PRINT_POINT("P0 BEFORE ROT", p0);

    Fixed angle = rad(20);
    Fixed rotZ[3][3] = {
        {fxcos(angle), -fxsin(angle), 0},
        {fxsin(angle),  fxcos(angle), 0},
        {0, 0, 1},
    };

    p0.applyRotMatrix(&rotZ);

    PRINT_POINT("P0 AFTER ROT", p0);
}
