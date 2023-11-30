#include <c64.h>
#include <stdint.h>
#include "render.h"
#include "fixedmath.h"

Renderer renderer;
int frameCount = 0;

const Point points[] = {
    Point(-25, -25),
    Point(-25,  25),
    Point( 25,  25),
    Point( 25, -25),
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

    Fixed angle = rad(frameCount * 2 % 90);

    Matrix3x3 rotZ = {
        {fxcos(angle), -fxsin(angle), 0},
        {fxsin(angle),  fxcos(angle), 0},
        {0, 0, 1},
    };

    // transform all points
    Point transformedPoints[4] = {
        points[0], points[1],
        points[2], points[3],
    };

    for (int i = 0; i < 4; i++) {
        Point *p = &transformedPoints[edges[i]];
        p->applyRotMatrix(&rotZ);
    }

    for (int i = 0; i < sizeof(edges) / sizeof(int); i += 2) {
        Point p0 = transformedPoints[edges[i]] + centerOffset;
        Point p1 = transformedPoints[edges[i + 1]] + centerOffset;
        renderer.drawLine(&p0, &p1, true);
    }

    // artificial delay
    // for (int i = 0; i < 0x1000; i++) {
    //     asm("nop");
    // }
}

int main() {
    renderer.init();
    while (true) {
        drawLoop();
        frameCount++;
    }
}
