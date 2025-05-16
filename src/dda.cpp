#include "dda.h"

bool DDA::isBlockInBounds(float bX, float bY, int w, int h) { return bX >= 0 && bX < w && bY >= 0 && bY < h; }

bool DDA::checkBlock(float bX, float bY, std::vector<std::vector<unsigned char>>& world) {
    bool var = isBlockInBounds(bX, bY, world[0].size(), world.size());
    if (var && world[bY][bX]) return true;
    return false;
}

DDA::rayCollision_t DDA::getCollisionDDAO1(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dY/dX;

    rayCollision_t rayCollision;

    float d0 = bY + 1 - ys - (bX + 1 - xs)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;
            rayCollision.CollisionType = 4;
            rayCollision.colOnWallFaceX = bX;
            rayCollision.colOnWallFaceY = bY + 1 - prevd0;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX, bY+1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY + 1;
            rayCollision.CollisionType = 1;
            rayCollision.colOnWallFaceX = bX + 1 + d0*dX/dY;
            rayCollision.colOnWallFaceY = bY+1;
            return rayCollision;
        }

        bX++;
        if (d0 <= 0) bY++;

        if (d0 > 0) prevd0 = d0;
        if (d0 <= 0) prevd0 = 1 + d0;
        if (d0 > 0) d0 -= slope;
        else d0 = d0 - slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO8(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dY/dX;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bY - ys - (bX + 1 - xs)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;
            rayCollision.CollisionType = 4;
            rayCollision.colOnWallFaceX = bX;
            rayCollision.colOnWallFaceY = bY - prevd0;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX, bY-1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY - 1;
            rayCollision.CollisionType = 3;
            rayCollision.colOnWallFaceX = bX + 1 + d0*dX/dY;
            rayCollision.colOnWallFaceY = bY;

            return rayCollision;
        }

        bX++;
        if (d0 >= 0) bY--;

        if (d0 < 0) prevd0 = d0;
        if (d0 >= 0) prevd0 = d0 - 1;
        if (d0 < 0) d0 -= slope;
        else d0 = d0 - slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO4(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dY/dX;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bY + 1 - ys + (xs - bX)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;
            rayCollision.CollisionType = 2;
            rayCollision.colOnWallFaceX = bX+1;
            rayCollision.colOnWallFaceY = bY + 1 - prevd0;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX, bY+1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY + 1;
            rayCollision.CollisionType = 1;
            rayCollision.colOnWallFaceX = bX + d0*dX/dY;
            rayCollision.colOnWallFaceY = bY + 1;

            return rayCollision;
        }

        bX--;
        if (d0 <= 0) bY++;

        if (d0 > 0) prevd0 = d0;
        else prevd0 = 1 + d0;

        if (d0 > 0) d0 += slope;
        else d0 = d0 + slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO5(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dY/dX;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bY - ys + (xs - bX)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 2;

            rayCollision.colOnWallFaceX = bX+1;
            rayCollision.colOnWallFaceY = bY - prevd0;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX, bY-1, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY - 1;

            rayCollision.CollisionType = 3;

            rayCollision.colOnWallFaceX = bX + d0*dX/dY;
            rayCollision.colOnWallFaceY = bY;

            return rayCollision;
        }

        bX--;
        if (d0 >= 0) bY--;

        if (d0 < 0) prevd0 = d0;
        else prevd0 = d0 - 1;

        if (d0 < 0) d0 += slope;
        else d0 = d0 + slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO2(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dX/dY;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bX + 1 - xs - (bY + 1 - ys)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 1;

            rayCollision.colOnWallFaceX = bX + 1 - prevd0;
            rayCollision.colOnWallFaceY = bY;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX+1, bY, world)) {
            rayCollision.blockX = bX+1;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 4;

            rayCollision.colOnWallFaceX = bX + 1;
            rayCollision.colOnWallFaceY = bY + 1 + d0*dY/dX;

            return rayCollision;
        }

        bY++;
        if (d0 <= 0) bX++;

        if (d0 > 0) prevd0 = d0;
        else prevd0 = d0 + 1;

        if (d0 > 0) d0 -= slope;
        else d0 = d0 - slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO7(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dX/dY;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bX + 1 - xs + (ys - bY)*slope;
    float prevd0 = d0 + slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;
            
            rayCollision.CollisionType = 3;

            rayCollision.colOnWallFaceY = bY + 1;
            rayCollision.colOnWallFaceX = bX + 1 - prevd0;

            return rayCollision;
        }
        if (d0 <= 0 && checkBlock(bX+1, bY, world)) {
            rayCollision.blockX = bX+1;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 4;

            rayCollision.colOnWallFaceX = bX+1;
            rayCollision.colOnWallFaceY = bY + d0*dY/dX;

            return rayCollision;
        }

        bY--;
        if (d0 <= 0) bX++;

        if (d0 > 0) prevd0 = d0;
        else prevd0 = d0 + 1;

        if (d0 > 0) d0 += slope;
        else d0 = d0 + slope + 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO6(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dX/dY;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bX - xs + (ys - bY)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 3;
            rayCollision.colOnWallFaceY = bY+1;
            rayCollision.colOnWallFaceX = bX - prevd0;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX-1, bY, world)) {
            rayCollision.blockX = bX-1;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 2;

            rayCollision.colOnWallFaceX = bX;
            rayCollision.colOnWallFaceY = bY + d0*dY/dX;

            return rayCollision;
        }

        bY--;
        if (d0 >= 0) bX--;

        if (d0 < 0) prevd0 = d0;
        else prevd0 = d0 - 1;
        
        if (d0 < 0) d0 += slope;
        else d0 = d0 + slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionDDAO3(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world) {
    float bX = trunc(xs);
    float bY = trunc(ys);

    float dX = xe - xs;
    float dY = ye - ys;

    float slope = dX/dY;

    rayCollision_t rayCollision;
    rayCollision.CollisionType = 0;

    float d0 = bX - xs - (bY + 1 - ys)*slope;
    float prevd0 = d0 - slope;

    while(bX >= 0 && bX < world[0].size() && bY >= 0 && bY < world.size()) {

        if (checkBlock(bX, bY, world)) {
            rayCollision.blockX = bX;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 1;

            rayCollision.colOnWallFaceY = bY;
            rayCollision.colOnWallFaceX = bX - prevd0;

            return rayCollision;
        }
        if (d0 >= 0 && checkBlock(bX-1, bY, world)) {
            rayCollision.blockX = bX-1;
            rayCollision.blockY = bY;

            rayCollision.CollisionType = 2;

            rayCollision.colOnWallFaceX = bX;
            rayCollision.colOnWallFaceY = bY + 1 + d0*dY/dX;

            return rayCollision;
        }

        bY++;
        if (d0 >= 0) bX--;

        if (d0 < 0) prevd0 = d0;
        else prevd0 = d0 - 1;

        if (d0 < 0) d0 -= slope;
        else d0 = d0 - slope - 1;
    }

    rayCollision.blockX = -1;
    return rayCollision;
}

DDA::rayCollision_t DDA::getCollisionInfo(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& worldMap) {
    float dX = xe - xs;
    float dY = ye - ys;
    rayCollision_t rayCollision;
    if (dX == 0 && dY == 0) {rayCollision.blockX = -1; return rayCollision;}
    if ((dX > 0 && dY >= 0 && dY <= dX)) {rayCollision = getCollisionDDAO1(xs, ys, xe, ye, worldMap);}
    else if ((dX >= 0 && dY > 0 && dY > dX)) rayCollision = getCollisionDDAO2(xs, ys, xe, ye, worldMap);
    else if (dX > 0 && dY < 0 && -dY <= dX) rayCollision = getCollisionDDAO8(xs, ys, xe, ye, worldMap);
    else if (dX > 0 && dY < 0 && -dY > dX) rayCollision = getCollisionDDAO7(xs, ys, xe, ye, worldMap);
    else if (dX < 0 && dY >= 0 && dY <= -dX) rayCollision = getCollisionDDAO4(xs, ys, xe, ye, worldMap);
    else if (dX <= 0 && dY > 0 && dY >= -dX) rayCollision = getCollisionDDAO3(xs, ys, xe, ye, worldMap);
    else if (dX < 0 && dY < 0 && dY >= dX) rayCollision = getCollisionDDAO5(xs, ys, xe, ye, worldMap);
    else if (dX <= 0 && dY < 0 && dY < dX) rayCollision = getCollisionDDAO6(xs, ys, xe, ye, worldMap);
    else rayCollision.blockX = -1;

    return rayCollision;
}