#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "vectorN.h"

class Game {
public:
    void init(const char*, int, int, int, int, bool);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    bool running;
    SDL_Window* win;
    SDL_Surface* winSurface;
    std::vector<std::vector<unsigned char>> worldMap;
};
