#include <c64.h>
#include <stdint.h>
#include "render.h"
#include "fixedmath.h"
#include <string.h>

Renderer renderer;
int frameCount = 0;

#define SIDELEN 30

const Point points[] = {
    Point(-SIDELEN, -SIDELEN,  SIDELEN),
    Point(-SIDELEN,  SIDELEN,  SIDELEN),
    Point( SIDELEN,  SIDELEN,  SIDELEN),
    Point( SIDELEN, -SIDELEN,  SIDELEN),
    Point(-SIDELEN, -SIDELEN, -SIDELEN),
    Point(-SIDELEN,  SIDELEN, -SIDELEN),
    Point( SIDELEN,  SIDELEN, -SIDELEN),
    Point( SIDELEN, -SIDELEN, -SIDELEN),
};

const int edges[] = {
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    3, 7,
};

const Point centerOffset = Point(320 / 2, 200 / 2);

void drawLoop() {
    renderer.clear();

    Fixed angle = Fixed(frameCount) / 10;
    Matrix3x3 rotX = {
        {1, 0, 0},
        {0,  fxcos(angle), fxsin(angle)},
        {0, -fxsin(angle), fxcos(angle)},
    };
    Matrix3x3 rotY = {
        { fxcos(angle), 0, fxsin(angle)},
        {0, 1, 0},
        {-fxsin(angle), 0, fxcos(angle)},
    };

    // transform all points
    Point transformedPoints[sizeof(points) / sizeof(Point)];
    memcpy((void *)transformedPoints, points, sizeof(points));

    for (int i = 0; i < sizeof(points) / sizeof(Point); i++) {
        Point *p = &transformedPoints[i];
        p->applyRotMatrix(rotX);
        p->applyRotMatrix(rotY);
    }

    for (int i = 0; i < sizeof(edges) / sizeof(int); i += 2) {
        Point p0 = transformedPoints[edges[i]] + centerOffset;
        Point p1 = transformedPoints[edges[i + 1]] + centerOffset;
        renderer.drawLine(&p0, &p1, true);
    }

    renderer.flush();
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
