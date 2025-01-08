#include "dda.h"

bool DDA::isBlockInBounds(float bX, float bY, int w, int h) { return bX >= 0 && bX < w && bY >= 0 && bY < h; }

bool DDA::checkBlock(float bX, float bY, std::vector<std::vector<unsigned char>>& world) {
    bool var = isBlockInBounds(bX, bY, world[0].size(), world.size());
    if (var) world[bY][bX] = 2;
    return false;
}

DDA::rayCollision_t DDA::getCollisionDDAO1(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bY + 1 - ys - (bX + 1 - xs)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX, bY+1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY + 1;
            return rayCollision;
        }

        bX++;
        if (d0 <= 0) bY++;

        prevd0 = d0;
        if (d0 > 0) d0 -= slope;
        else d0 = d0 - slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO8(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bY - ys - (bX + 1 - xs)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX, bY-1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY - 1;
            return rayCollision;
        }

        bX++;
        if (d0 >= 0) bY--;

        prevd0 = d0;
        if (d0 < 0) d0 -= slope;
        else d0 = d0 - slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO4(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bY + 1 - ys + (xs - bX)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX, bY+1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY + 1;
            return rayCollision;
        }

        bX--;
        if (d0 <= 0) bY++;

        prevd0 = d0;
        if (d0 > 0) d0 += slope;
        else d0 = d0 + slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO5(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bY - ys + (xs - bX)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX, bY-1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY - 1;
            return rayCollision;
        }

        bX--;
        if (d0 >= 0) bY--;

        prevd0 = d0;
        if (d0 < 0) d0 += slope;
        else d0 = d0 + slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO2(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bX + 1 - xs - (bY + 1 - ys)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX+1, bY, world)) {
            rayCollision.blockX = bX+1;
            rayCollision.blockY = bY;
            return rayCollision;
        }

        bY++;
        if (d0 <= 0) bX++;

        prevd0 = d0;
        if (d0 > 0) d0 -= slope;
        else d0 = d0 - slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO7(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bX + 1 - xs + (ys - bY)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX+1, bY, world)) {
            rayCollision.blockX = bX+1;
            rayCollision.blockY = bY;
            return rayCollision;
        }

        bY--;
        if (d0 <= 0) bX++;

        prevd0 = d0;
        if (d0 > 0) d0 += slope;
        else d0 = d0 + slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO6(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bX - xs + (ys - bY)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX-1, bY, world)) {
            rayCollision.blockX = bX-1;
            rayCollision.blockY = bY;
            return rayCollision;
        }

        bY--;
        if (d0 >= 0) bX--;

        prevd0 = d0;
        if (d0 < 0) d0 += slope;
        else d0 = d0 + slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO3(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    rayCollision_t rayCollision;

    float d0 = bX - xs - (bY + 1 - ys)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX-1, bY, world)) {
            rayCollision.blockX = bX-1;
            rayCollision.blockY = bY;
            return rayCollision;
        }

        bY++;
        if (d0 >= 0) bX--;

        prevd0 = d0;
        if (d0 < 0) d0 -= slope;
        else d0 = d0 - slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}