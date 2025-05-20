#ifndef Graphics_h
#define Graphics_h

#include <vector>
#include "vectorN.h"
#include <SDL2/SDL.h>
#include "dda.h"
#include <cmath>

struct Camera {
	int px_w, px_h;
	float cam_w, cam_h;
	float focal_length;
	float pos_x, pos_y;
	float rlz, rly;
	SDL_Surface* winSurface;
};

class GraphicsHandler {
private:
	Camera* cam;
	std::vector<std::vector<unsigned char>> map;
	void set_pixel(SDL_Surface *surface, int x, int y, Uint32 color);
	float world_height;

public:
	void init (Camera* cam_ptr, std::vector<std::vector<unsigned char>>& map_matrix, int world_height);
	void render();
};

#endif