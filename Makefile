SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

build/executable/program: src/main.cpp src/game.h src/game.cpp src/vectorN.h src/vectorN.cpp src/graphics.h src/graphics.cpp
	g++ -Wall -g -o build/executable/program src/main.cpp src/game.cpp src/vectorN.cpp src/graphics.cpp $(SDL_CFLAGS) $(SDL_LDFLAGS)
