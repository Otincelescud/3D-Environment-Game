#include <SDL2/SDL.h>
#include "game.h"

int main(int argc, char *argv[]) {
    Game *game = new Game;

    game->init("3DEnv", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, false);
    while (game->isRunning()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();

    delete game;

    return 0;
}
