#pragma once

class Renderer {
public:
    void init();
    void clear();
    void setPixel(unsigned int x, unsigned int y, unsigned char clr);
    void drawLine(int x0, int y0, int x1, int y1, unsigned char clr);
};
