#include "fixed.h"

#define FP_BITS 16
#define FP_DOWN(x) ((_FixedRaw)(x) >> FP_BITS)
#define FP_UP(x) ((_FixedRaw)(x) << FP_BITS)

Fixed::Fixed(int i) : _v(FP_UP(i)) {}
Fixed::Fixed() : _v(0) {}

Fixed Fixed::raw(_FixedRaw v) {
    auto newFixed = Fixed();
    newFixed._v = v;
    return newFixed;
}

_FixedRaw Fixed::raw() {
    return _v;
}

// casts
Fixed::operator int() const {
    return FP_DOWN(_v);
}

// unary ops
Fixed Fixed::operator-() const {
    auto newFixed = Fixed();
    newFixed._v = -_v;
    return newFixed;
}

// int ops
Fixed Fixed::operator+(const int &other) const {
    auto newFixed = Fixed();
    newFixed._v = _v + FP_UP(other);
    return newFixed;
}

Fixed Fixed::operator*(const int &other) const {
    auto newFixed = Fixed();
    newFixed._v = _v * other;
    return newFixed;
}

Fixed Fixed::operator/(const int &other) const {
    auto newFixed = Fixed();
    newFixed._v = _v / other;
    return newFixed;
}

// fixed ops
Fixed &Fixed::operator+=(const Fixed &other) {
    _v = _v + other._v;
    return *this;
}

Fixed Fixed::operator+(const Fixed &other) const {
    auto newFixed = Fixed();
    newFixed._v = _v + other._v;
    return newFixed;
}

Fixed Fixed::operator-(const Fixed &other) const {
    auto newFixed = Fixed();
    newFixed._v = _v - other._v;
    return newFixed;
}

Fixed Fixed::operator*(const Fixed &other) const {
    auto newFixed = Fixed();
    newFixed._v = FP_DOWN(_v * other._v);
    return newFixed;
}
