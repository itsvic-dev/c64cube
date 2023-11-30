#include <c64.h>
#include <stdint.h>
#include "render.h"

Renderer renderer;
int frameCount = 0;

void drawLoop() {
    renderer.clear();
    renderer.drawLine(Point(0, 0), Point(100, 50), 1);
}

int main() {
    renderer.init();
    while (true) {
        drawLoop();
        frameCount++;
    }
}
