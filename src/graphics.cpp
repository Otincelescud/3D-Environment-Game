#include "graphics.h"

// If the window surface has resolution of 1920px by 1280px, then we think of the digital camera as having a standard full frame sensor which has the dimensions of 36mm by 24mm. if we change the number of pixels on the horizontal or the vertical the digital camera sensor will be scaled with it. We can think that the dimensions of a digital camera sensor pixel remain constant and the width and height of the sensor can vary. This is not realistic at all and it is also not entirely correct to implement it this way. However as this is just a fun program i dont want to implement aspect ratio and also, this way of doing things should work just fine (i think).

void Graphics::init(SDL_Surface* winSurf, float fLen, float RDistance, Vector<3>* CamPosPtr, Vector<3>* CamRotPtr, std::vector<std::vector<unsigned char>>* wPtr) {
	winSurface = winSurf;
	focalLength = fLen;
	renderDistance = RDistance;
	CameraPositionPtr = CamPosPtr;
	CameraRotationPtr = CamRotPtr;
	worldPtr = wPtr;
	worldWidth = wPtr->size();
	worldHeight = *wPtr[0].size();
}

void Graphics::render() {
	if (SDL_MUSTLOCK(winSurface)) {
		SDL_LockSurface(winSurface);
	}

	for (int y = 0; y < winSurface->h; ++y) {
		for (int x = 0; x < winSurface->w; ++x) {
			Uint32* pixel = (Uint32*)winSurface->pixels + y * winSurface->w + x;
			Vector<2> pixel_vector; pixel_vector[0] = x; pixel_vector[1] = y;
			*pixel = getPixelColor(pixel_vector);
		}
	}

	if (SDL_MUSTLOCK(winSurface)) {
		SDL_UnlockSurface(winSurface);
	}
}
Vector<3> Graphics::getVectorForPixel(const Vector<2>& pixelVector) const {
	const float wInMm = float(winSurface->w - 1)*36/1920, hInMm = float(winSurface->h - 1)*36/1920;
	Vector<2> vectorToMiddleOfSensor; vectorToMiddleOfSensor[0] = wInMm/2; vectorToMiddleOfSensor[1] = hInMm/2;
	Vector<2> pixelVectorInMm = pixelVector*36/1920;	
	Vector<2> vectorFromMiddleOfSensor = pixelVectorInMm - vectorToMiddleOfSensor;
	vectorFromMiddleOfSensor[1] = -vectorFromMiddleOfSensor[1];
	Vector<3> unnormalised_result; unnormalised_result[0] = vectorFromMiddleOfSensor[0];
	unnormalised_result[1] = vectorFromMiddleOfSensor[1];
	unnormalised_result[2] = focalLength;
	
	return unnormalised_result / unnormalised_result.norm();	
}

Uint32 Graphics::getPixelColor(const Vector<2>& pixelVector) const {
	Uint32 color = 0;
	Vector<3> rayDirectionVector = getVectorForPixel(pixelVector);
	Vector<3> rayDirectionVectorBasedOnWorldAxisSystem = changeAxisSystemForRayDirectionVector(rayDirectionVector);
	Vector<3>& 3D = rayDirectionVectorBasedOnWorldAxisSystem;
	Vector<2> 2D; 2D[0] = 3D[0]; 2D[1] = 3D[1];
	Vector<2> intersectedBlock;
	Vector<2> currentBlock; currentBlock[0] = floor(2D[0]); currentBlock[1] = floor(2D[1]);
	Vector<2> checked; checked[0] = currentBlock[1] + (2D[0] > 0) ? 1 : 0; currentBlock[1] + (2D[0] > 0) ? 1 : 0;
	Vector<2> incrementAmount; incrementAmount[0] = (2D[0] > 0) ? 1 : -1; incrementAmount[1] = (2D[1] > 0) ? 1 : -1;
	Vector<2> scalars; scalars[0] = -1; scalars[1] = -1; 
	Vector<2> intersectFound; intersectFound[0] = 0; intersectFound[1] = 0;
	while (checked[0] > 0 && checked[0] < worldWidth && scalars[0] <= renderRadius && checked[1] > 0 && checked[1] < worldHeight && scalars[1] <= renderRadius && !intersectFound[0] && !intersectFound[1]) {
		// Get value if needed, check if it is within render radius, then check if it is an intersected block, do these for both Row and Col Scalars.
		scalars[0] = getScalarOfIntersectionwithGridline<false>(checked[0]);
		Vector<2> block;
		if (scalars[0] <= renderRadius) block = getBlockFromScalar(2D, scalars[0]);
		// If both Col and Row searches are intersections, check which is smaller. If they are equal (this should mean that the intersection happened perfectly on/very near a block corner) choose scalarForRow as the valid intersection (we are considering the intersection on the corner a row intersection).


		checked = checked + incrementAmount;
	}
}
