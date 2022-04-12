#include "FBWindowManager.h"

int main() {
    World WORLD(40, 288, 512);
    FBWindowManager game_window(WORLD);

    initgraph(WORLD.getWidth(), WORLD.getHeight(), 1);
    game_window.windowLoop();
    return EXIT_SUCCESS;
}
