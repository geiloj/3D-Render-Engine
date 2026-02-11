#include "Cube.h"

Cube::Cube()
{
}

Cube::Cube(Point position, Point dimension)
{
	Cube::position = position;
	Cube::dimensions = dimension;
}

Cube::Cube(const Cube& other)
{
	Cube::position = other.position;
	Cube::dimensions = other.dimensions;
}

Cube& Cube::operator=(const Cube& other)
{
	if (this != &other) {
		position = other.position;
		dimensions = other.dimensions;
	}
	return *this;
	// TODO: hier return-Anweisung eingeben
}
