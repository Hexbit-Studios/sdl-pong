#include "game.h"

int main(int argc, char** argv) {
    Game game;
    if (game.init()) {
        game.run();
    }
    game.shutdown();
    return 0;
}