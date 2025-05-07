#ifndef DDA_h
#define DDA_h

#include <cmath>
#include <vector>

namespace DDA {
    typedef struct {
        int blockX;
        int blockY;
        int CollisionType;
        float posOnWallFace;
    } rayCollision_t;

    bool isBlockInBounds(float bX, float bY, int w, int h);
    bool checkBlock(float bX, float bY, std::vector<std::vector<unsigned char>>& world);

    rayCollision_t getCollisionDDAO1(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO8(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO4(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO5(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO2(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO7(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO6(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);
    rayCollision_t getCollisionDDAO3(float xs, float ys, float slope, std::vector<std::vector<unsigned char>>& world);

    rayCollision_t getCollisionInfo(float xs, float ys, float xe, float ye, std::vector<std::vector<unsigned char>>& world);
}

#endif