#pragma once
#define inherit
#include "Body.h"
#include "VCube.h"
class Cube : public Body
{
	public:
		Cube();
		Cube(Point position, Point dimension);
		Cube(const Cube& other);
		Cube& operator=(const Cube& other);
};

