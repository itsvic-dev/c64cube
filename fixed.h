#pragma once
#include <stdint.h>

typedef int64_t _FixedRaw;

class Fixed {
public:
    Fixed(int i);
    static Fixed raw(_FixedRaw v);
    _FixedRaw raw();

    // casts
    operator int() const;
    // unary ops
    Fixed operator-() const;
    // int ops
    Fixed operator+(const int &other) const;
    Fixed operator*(const int &other) const;
    Fixed operator/(const int &other) const;
    // fixed ops
    Fixed &operator+=(const Fixed &other);
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

private:
    Fixed();
    _FixedRaw _v;
};
