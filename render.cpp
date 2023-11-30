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

void Renderer::setPixel(unsigned int x, unsigned int y, unsigned char clr) {
    // get the 8x8 pixel block
    unsigned int blockX = x / 8;
    unsigned int blockY = y / 8;
    volatile unsigned char *block = &BITMAP_RAM[(blockY * (320 / 8) + blockX) * 8];
    // now get the position inside the block
    unsigned int bPosX = x % 8;
    unsigned int bPosY = y % 8;
    // now set or clear the bit
    if (clr) {
        block[bPosY] |= 1 << (7 - bPosX);
    } else {
        block[bPosY] &= ~(1 << (7 - bPosX));
    }
}

// thx chatgpt
void Renderer::drawLine(int x0, int y0, int x1, int y1, unsigned char clr) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        setPixel(x0, y0, clr);
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