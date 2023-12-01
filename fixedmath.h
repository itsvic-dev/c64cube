#pragma once
#include "fixed.h"

#define TRIG_ACCURACY 32

#define PI (Fixed::raw(205887))

static inline Fixed rad(Fixed deg) {
    return (deg * PI) / 180;
}

Fixed fxsin(Fixed x);
Fixed fxcos(Fixed x);
