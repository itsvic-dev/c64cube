#include "render.h"
#include <c64.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_RAM ((volatile unsigned char *)0x8400)
#define BITMAP_RAM ((volatile unsigned char *)0xa000)

void Renderer::init() {
    // set up the VIC-II
    CIA2.pra = 1; // move VIC's base to 0x8000
    VIC.bordercolor = 16;
    VIC.ctrl1 |= (1 << 5); // set BMM byte of CR1 to enable bitmap mode
    VIC.addr = 0x18; // put screen RAM at 0x400, bitmap RAM at 0x2000

    // clean and set up screen
    memset((void *)SCREEN_RAM, 0xf0, 1024); // black bg, white fg
}

void Renderer::clear() {
    memset((void *)buffer, 0, 0x2000);
}

void Renderer::flush() {
    memcpy((void *)BITMAP_RAM, buffer, 0x2000);
}

void Renderer::setPixel(const Point *p, bool clr) {
    if (p->x >= 320 || p->y >= 200 || p->x < 0 || p->y < 0) return;
    // get the 8x8 pixel block
    unsigned int blockIndex = (p->y >> 3) * 40 + (p->x >> 3);
    volatile unsigned char *block = &buffer[blockIndex * 8];
    // now get the position inside the block
    uint8_t bPosX = p->x % 8;
    uint8_t bPosY = p->y % 8;
    // now set or clear the bit
    if (clr) {
        block[bPosY] |= 1 << (7 - bPosX);
    } else {
        block[bPosY] &= ~(1 << (7 - bPosX));
    }
}

// http://www.edepot.com/lined.html
void Renderer::drawLine(const Point *p0, const Point *p1, bool clr) {
    int16_t x = p0->x;
    int16_t y = p0->y;
    int16_t x2 = p1->x;
    int16_t y2 = p1->y;
    bool yLonger = false;
    int16_t incVal = 1;
    int16_t endVal = 0;
    int16_t shortLen = y2 - y;
    int16_t longLen = x2 - x;
    if (abs(shortLen) > abs(longLen)) {
        int16_t swap = shortLen;
        shortLen = longLen;
        longLen = swap;
        yLonger = true;
    }

    endVal = longLen;

    if (longLen < 0) {
        incVal = -1;
        longLen = -longLen;
    }
    int16_t decInc = 0;
    if (longLen) { decInc = (shortLen << 8) / longLen; }
    int16_t j = 0;
    Point p;

    for (int16_t i = 0; i != endVal; i += incVal) {
        p = Point(x + i, y + (j >> 8));
        if (yLonger) { p = Point(x + (j >> 8), y + i); }
        setPixel(&p, clr);
        j += decInc;
    }
}
