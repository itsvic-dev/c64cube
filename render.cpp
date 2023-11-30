#include "render.h"
#include <c64.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_RAM ((volatile unsigned char *)0x400)
#define BITMAP_RAM ((volatile unsigned char *)0x2000)

void Renderer::init() {
    // set up the VIC-II
    VIC.bordercolor = 16;
    VIC.ctrl1 |= (1 << 5); // set BMM byte of CR1 to enable bitmap mode
    VIC.addr = 0x18; // put screen RAM at 0x400, bitmap RAM at 0x2000

    // clean and set up screen
    memset((void *)SCREEN_RAM, 0xf0, 1024); // black bg, white fg
    clear();
}

void Renderer::clear() {
    memset((void *)BITMAP_RAM, 0, 0x2000);
}

void Renderer::setPixel(const Point &p, bool clr) {
    // get the 8x8 pixel block
    unsigned int blockX = p.x >> 3;
    unsigned int blockY = p.y >> 3;
    volatile unsigned char *block = &BITMAP_RAM[(blockY * 40 + blockX) * 8];
    // now get the position inside the block
    unsigned int bPosX = p.x % 8;
    unsigned int bPosY = p.y % 8;
    // now set or clear the bit
    if (clr) {
        block[bPosY] |= 1 << (7 - bPosX);
    } else {
        block[bPosY] &= ~(1 << (7 - bPosX));
    }
}

// thx chatgpt
void Renderer::drawLine(const Point &p0, const Point &p1, bool clr) {
    int16_t x0 = p0.x;
    int16_t y0 = p0.y;
    int16_t x1 = p1.x;
    int16_t y1 = p1.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        setPixel(Point(x0, y0), clr);
        int err2 = 2 * err;
        
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}