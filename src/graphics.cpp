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

void GraphicsHandler::init(Camera* cam_ptr, std::vector<std::vector<unsigned char>>& map_matrix) {
    cam = cam_ptr;
    map = map_matrix;
}

void GraphicsHandler::render() {
    for (int j = 0; j < cam->px_h; j++) {
        for (int i = 0; i < cam->px_w; i++) {
            Vector<3> ray_vector;
            ray_vector[0] = cam->focal_length;
            ray_vector[1] = i*cam->cam_w/cam->px_w - cam->cam_w/2;
            ray_vector[2] = (cam->px_h - 1 - j)*cam->cam_h/cam->px_h - cam->cam_h/2;

            ray_vector = ray_vector/ray_vector.norm();

            DDA::rayCollision_t px_info = DDA::getCollisionInfo(cam->pos_x, cam->pos_y, cam->pos_x + cos(cam->rly)*cos(cam->rlz)*ray_vector[0] + -sin(cam->rlz)*ray_vector[1] + -sin(cam->rly)*cos(cam->rlz)*ray_vector[2], cam->pos_y + cos(cam->rly)*sin(cam->rlz)*ray_vector[0] + cos(cam->rlz)*ray_vector[1] + -sin(cam->rly)*sin(cam->rlz)*ray_vector[2], map);
            Uint32 color = SDL_MapRGB(cam->winSurface->format, 255, 0, 0);
            set_pixel(cam->winSurface, i, j, color);
            if (px_info.blockX != -1 && map[px_info.blockY][px_info.blockX] == 1) {
                Uint32 color = SDL_MapRGB(cam->winSurface->format, 255, 0, 0);
                if (px_info.CollisionType % 2 == 1 && int(trunc(px_info.colOnWallFaceX*4))%2 == 0) color = SDL_MapRGB(cam->winSurface->format, 255, 255, 0);
                if (px_info.CollisionType % 2 == 0 && int(trunc(px_info.colOnWallFaceY*4))%2 == 0) color = SDL_MapRGB(cam->winSurface->format, 255, 255, 0);
                set_pixel(cam->winSurface, i, j, color);
            }
            else if (px_info.blockX != -1 && map[px_info.blockY][px_info.blockX] == 2) {
                Uint32 color = SDL_MapRGB(cam->winSurface->format, 0, 255, 0);
                if (px_info.CollisionType % 2 == 1 && int(trunc(px_info.colOnWallFaceX*4))%2 == 0) color = SDL_MapRGB(cam->winSurface->format, 0, 255, 255);
                if (px_info.CollisionType % 2 == 0 && int(trunc(px_info.colOnWallFaceY*4))%2 == 0) color = SDL_MapRGB(cam->winSurface->format, 0, 255, 255);
                set_pixel(cam->winSurface, i, j, color);
            }
            else {
                Uint32 color = SDL_MapRGB(cam->winSurface->format, 0, 0, 0);
                set_pixel(cam->winSurface, i, j, color);
            }
        }
    }
}