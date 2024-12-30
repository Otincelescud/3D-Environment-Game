#ifndef Graphics_h
#define Graphics_h

#include <SDL2/SDL.h>
#include <vector>
#include "vectorN.h"
#include <iostream>
#include <cmath>

class Graphics {
public:
	void init(SDL_Surface*, float, float, Vector<3>*, Vector<3>*, std::vector<std::vector<unsigned int>>*);
	void render();

private:
	SDL_Surface* winSurface;
	float focalLength;
	float renderDistance;
	Vector<3>* CameraPositionPtr;
	Vector<3>* CameraRotationPtr;
	std::vector<std::vector<unsigned char>>* worldPtr;
	int worldWidth;
	int worldHeight;

	Vector<3> getVectorForPixel(const Vector<2>&) const;
	template<bool B> float getScalarOfIntersectWithGridline(const int) const;
	// If the returned float is bigger than the render radius, then either the ray intersects a gridline too far away from the camera or is paralel or coliniar to the gridline we are checking for intersection. In this case the value returned by this function should be ignored as it is either invalid or inconsequnetial to the final rendered image.
	Vector<2> getBlockFromScalar(const Vector<2>&, const float) const;
	float getIntersectionHeightFromScalar(const Vector<3>&, const float) const;
	// float getIntersectionAngleFrom3DIntersectionCords(const Vector<3>&, bool) const; -> This One Might Not Be Needed
	Vector<3> changeAxisSystemForRayDirectionVector(const Vector<3>&) const;
	Uint32 getPixelColor(const Vector<2>&) const;
};

#endif /* Graphics_h */
