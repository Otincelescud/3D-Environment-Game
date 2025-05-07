SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LDFLAGS := $(shell pkg-config --libs sdl2)

build/executable/program: src/main.cpp src/game.h src/game.cpp src/vectorN.h src/vectorN.cpp src/graphics.h src/graphics.cpp src/dda.h src/dda.cpp
	g++ -Wall -g -o build/executable/program src/main.cpp src/game.cpp src/vectorN.cpp src/graphics.cpp src/dda.cpp $(SDL_CFLAGS) $(SDL_LDFLAGS)
