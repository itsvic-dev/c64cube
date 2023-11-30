#pragma once
#include "fixed.h"

#define TRIG_ACCURACY 8

#define PI (Fixed::raw(205887ll))

static Fixed rad(Fixed deg) {
    return (deg * PI) / 180;
}

static Fixed fxsin(Fixed x) {
    Fixed result = 0;
    Fixed term = x;

    for (int i = 1; i <= TRIG_ACCURACY; ++i) {
        result += term;
        term = -term * x * x / ((2 * i) * (2 * i + 1));
    }

    return result;
}

static Fixed fxcos(Fixed x) {
    Fixed result = 0;
    Fixed term = x;

    for (int i = 1; i <= TRIG_ACCURACY; ++i) {
        term = -term * x * x / ((2 * i - 1) * (2 * i));
        result += term;
    }

    return result;
}
