#include "game.h"

bool Game::isRunning() { return running; }


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cerr << "Can't Initialize SDL." << '\n'; return; }

    win = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!win) { std::cerr << "Can't Create Window: " << SDL_GetError() << '\n'; return; }
    
    winSurface = SDL_GetWindowSurface(win);
    if (!winSurface) { std::cerr << "Can't Get Window Surface: " << SDL_GetError() << '\n'; return; }

    cam.px_w = width;
    cam.px_h = height;
    cam.cam_w = 36;
    cam.cam_h = 24;
    cam.focal_length = 50;
    cam.pos_x = 0; cam.pos_y = 0;
    cam.rly = 0; cam.rlz = 0;
    cam.winSurface = winSurface;

    worldMap = {
        {0, 0, 1},
        {0, 1, 0},
        {0, 0, 0}
    };

	graphicsHandler.init(&cam, worldMap);

    running = true;
}


void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update() {

}

void Game::render() {
	graphicsHandler.render();
    SDL_UpdateWindowSurface( win );
}

void Game::clean() {
    SDL_DestroyWindow(win);
    SDL_Quit();
}
