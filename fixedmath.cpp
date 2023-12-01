#include "fixedmath.h"
#include "_sinlut.h"

Fixed fxsin(Fixed x) {
    int idx = (x * SINLUT_ENTRIES / (2 * PI)) % SINLUT_ENTRIES;
    return Fixed::raw(sinlut[idx]);
}

Fixed fxcos(Fixed x) {
    int idx = (x * SINLUT_ENTRIES / (2 * PI)) % SINLUT_ENTRIES;
    return Fixed::raw(coslut[idx]);
}
