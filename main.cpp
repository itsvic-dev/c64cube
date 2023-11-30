#include <c64.h>
#include <stdint.h>
#include "render.h"

Renderer renderer;
int frameCount = 0;

const Point points[] = {
    Point(-50, -50),
    Point(-50,  50),
    Point( 50,  50),
    Point( 50, -50),
};

const int edges[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0,
};

const Point centerOffset = Point(320 / 2, 200 / 2);

void drawLoop() {
    renderer.clear();
    for (int i = 0; i < sizeof(edges) / sizeof(int); i += 2) {
        const Point p0 = points[edges[i]] + centerOffset;
        const Point p1 = points[edges[i + 1]] + centerOffset;
        renderer.drawLine(p0, p1, 1);
    }
}

int main() {
    renderer.init();
    while (true) {
        drawLoop();
        frameCount++;
    }
}
