#include "graphics.h"

void Graphics_handler::init(Camera* cam_ptr, std::vector<std::vector<unsigned char>> map_matrix) {
    cam = cam_ptr;
    map = map_matrix;
}

void Graphics_handler::render(SDL_Surface* winSurface) {
    for (int i = 0; i < cam->px_w; i++) {
        for (int j = 0; j < cam->px_h; j++) {
            Vector<3> ray_vector;
            ray_vector[0] = cam->focal_length;
            ray_vector[1] = i*cam->cam_w/cam->px_w - cam->cam_w/2;
            ray_vector[2] = (cam->px_h - 1 - j)*cam->cam_h/cam->px_h - cam->cam_h/2;

            ray_vector = ray_vector/ray_vector.norm();

            DDA::rayCollision_t px_info = DDA::getCollisionInfo(cam->pos_x, cam->pos_y, cam->pos_x + cos(cam->rly)*cos(cam->rlz)*ray_vector[0] + -sin(cam->rlz)*ray_vector[1] + -sin(cam->rly)*cos(cam->rlz)*ray_vector[2], cos(cam->rly)*sin(cam->rlz)*ray_vector[0] + cos(cam->rlz)*ray_vector[1] + -sin(cam->rly)*sin(cam->rlz)*ray_vector[2], map);
            // color pixel
        }
    }
}