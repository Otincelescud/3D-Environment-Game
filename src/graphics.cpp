#include "graphics.h"

void GraphicsHandler::set_pixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            *p = color;
            break;

        case 2:
            *(Uint16 *)p = color;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (color >> 16) & 0xFF;
                p[1] = (color >> 8) & 0xFF;
                p[2] = color & 0xFF;
            } else {
                p[0] = color & 0xFF;
                p[1] = (color >> 8) & 0xFF;
                p[2] = (color >> 16) & 0xFF;
            }
            break;

        case 4:
            *(Uint32 *)p = color;
            break;
    }
}

void GraphicsHandler::init(Camera* cam_ptr, std::vector<std::vector<unsigned char>>& map_matrix, int w_height) {
    cam = cam_ptr;
    map = map_matrix;
    world_height = w_height;
}

void GraphicsHandler::render() {
    for (int j = 0; j < cam->px_h; j++) {
        for (int i = 0; i < cam->px_w; i++) {
            Vector<3> ray_vector;
            ray_vector[0] = cam->focal_length;
            ray_vector[1] = i*cam->cam_w/cam->px_w - cam->cam_w/2;
            ray_vector[2] = (cam->px_h - 1 - j)*cam->cam_h/cam->px_h - cam->cam_h/2;

            ray_vector = ray_vector/ray_vector.norm();

            Vector<3> rotated_ray_vector;
            rotated_ray_vector[0] = cos(cam->rly)*cos(cam->rlz)*ray_vector[0] + -sin(cam->rlz)*ray_vector[1] + -sin(cam->rly)*cos(cam->rlz)*ray_vector[2];
            rotated_ray_vector[1] = cos(cam->rly)*sin(cam->rlz)*ray_vector[0] + cos(cam->rlz)*ray_vector[1] + -sin(cam->rly)*sin(cam->rlz)*ray_vector[2];
            rotated_ray_vector[2] = sin(cam->rly)*ray_vector[0] + cos(cam->rly)*ray_vector[2];


            DDA::rayCollision_t px_info = DDA::getCollisionInfo(cam->pos_x, cam->pos_y, cam->pos_x + rotated_ray_vector[0], cam->pos_y + rotated_ray_vector[1], map);
            Uint32 color = SDL_MapRGB(cam->winSurface->format, 0, 0, 0);
            set_pixel(cam->winSurface, i, j, color);

            // from here on this needs to be redone and put into multiple functions

            float z_coord;
            if (rotated_ray_vector[0] == 0) z_coord = rotated_ray_vector[2]*(px_info.colOnWallFaceY - cam->pos_y)/rotated_ray_vector[1];
            else z_coord = rotated_ray_vector[2]*(px_info.colOnWallFaceX - cam->pos_x)/rotated_ray_vector[0];

            Uint32 roof_color = SDL_MapRGB(cam->winSurface->format, 75, 10, 5);
            Uint32 floor_color = SDL_MapRGB(cam->winSurface->format, 100, 100, 100);

            SDL_Surface* tex;
            int tex_x;
            int tex_y;
            Uint32 px_color;

            if (px_info.blockX != -1 && z_coord > -1.5 && z_coord < -1.5 + world_height) {
                // Render Walls
                tex_y = 12*(z_coord + 1.5);
                if (px_info.CollisionType == 1) {
                    tex_x = 12*(px_info.colOnWallFaceX - px_info.blockX);
                }
                else if (px_info.CollisionType == 2) {
                    tex_x = 12 + 12*(px_info.colOnWallFaceY - px_info.blockY); // Make a variabble for num pixels per wall
                }
                else if (px_info.CollisionType == 3) {
                    tex_x = 24 + 12*(1 - px_info.colOnWallFaceX + px_info.blockX);
                }
                else {
                    tex_x = 36 + 12*(1 - px_info.colOnWallFaceY + px_info.blockY);
                }

                Uint32 color1 = SDL_MapRGB(cam->winSurface->format, 255, 0, 0);
                Uint32 altColor1 = SDL_MapRGB(cam->winSurface->format, 255, 255, 0);
                Uint32 color2 = SDL_MapRGB(cam->winSurface->format, 0, 255, 0);
                Uint32 altColor2 = SDL_MapRGB(cam->winSurface->format, 0, 255, 255);

                if (map[px_info.blockY][px_info.blockX] == 1) {
                    px_color = color1;
                    if (int((float)tex_x / 48 * 16) % 2 == int((float)tex_y / 12 * 4) % 2) px_color = altColor1;
                    set_pixel(cam->winSurface, i, j, px_color);
                }
                else if (map[px_info.blockY][px_info.blockX] == 2) {
                    px_color = color2;
                    if (int((float)tex_x / 48 * 16) % 2 == int((float)tex_y / 12 * 4) % 2) px_color = altColor2;
                    set_pixel(cam->winSurface, i, j, px_color);
                }
            }
            else {
                // Render roof / floor
                if (rotated_ray_vector[2] >= 0) px_color = roof_color;
                else px_color = floor_color;
                set_pixel(cam->winSurface, i, j, px_color);
            }
        }
    }
}