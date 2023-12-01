#pragma once
#include <stdint.h>
#include "point.h"

class Renderer {
public:
    void init();
    void clear();
    void setPixel(const Point *p, bool clr);
    void drawLine(const Point *p0, const Point *p1, bool clr);
    void flush();

private:
    unsigned char buffer[0x2000];
};
