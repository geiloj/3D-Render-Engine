#pragma once
#include "Point.h"
class Camera
{
public:
	Point position;
	Point direction;
	Camera(Point position, Point direction);
};