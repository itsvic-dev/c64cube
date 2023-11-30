#include <c64.h>
#include <stdio.h>
#include "render.h"

Renderer renderer;

int main() {
    renderer.init();

    renderer.drawLine(0, 0, 319, 199, 1);

    // LLVM optimizes this loop away since
    // it does nothing, so i snuck a NOP
    // in here so we don't end up returning
    // to BASIC
    while (true) {
        asm("nop");
    }
}
