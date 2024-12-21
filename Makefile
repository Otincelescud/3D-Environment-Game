SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

program: src/main.cpp src/game.h src/game.cpp
	g++ -Wall -g -o build/executable/program src/main.cpp src/game.cpp $(SDL_CFLAGS) $(SDL_LDFLAGS)