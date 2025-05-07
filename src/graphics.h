#ifndef Graphics_h
#define Graphics_h

#include <vector>
#include <vectorN.h>
#include <SDL2/SDL.h>
#include <dda.h>
#include <cmath>

struct Camera {
	int px_w, px_h;
	int cam_w, cam_h;
	int focal_length;
	int pos_x, pos_y;
	int rlz, rly;
	SDL_Surface* winSurface;
};

class Graphics_handler {
private:
	Camera* cam;
	std::vector<std::vector<unsigned char>> map;

public:
	void init (Camera* cam_ptr, std::vector<std::vector<unsigned char>> map_matrix);
	void render(SDL_Surface* winSurface);
};

#endif