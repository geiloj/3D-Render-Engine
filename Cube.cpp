#include "Cube.h"
Cube::Cube()
{
}
Cube::Cube(Point position, Point dimension)
{
	clean();
	Cube::position = position;
	Cube::dimensions = dimensions;
	for (int i = 0;i < std::size(verticies);i++) {
		o_verticies[i].x = verticies[i].x + position.x;
		o_verticies[i].y = verticies[i].y + position.y;
		o_verticies[i].z = verticies[i].z + position.z;
	}
}
Cube::Cube(const Cube& other)
	: position(other.position),
	dimensions(other.dimensions){
	for (int i = 0; i < 8; ++i) {
		o_verticies[i] = other.o_verticies[i];
	}
}

Cube& Cube::operator=(const Cube& other)
{
	if (this != &other) {
		position = other.position;
		dimensions = other.dimensions;
		for (int i = 0; i < 8; ++i) {
			o_verticies[i] = other.o_verticies[i];
		}
	}
	return *this;
}

void Cube::setPosition(Point position)
{
	Cube::position = position;
	for (int i = 0;i < std::size(verticies);i++) {
		verticies[i].x = position.x;
		verticies[i].y = position.y;
		verticies[i].z = position.z;
	}
}

void Cube::move(Point position)
{
	for (int i = 0;i < std::size(verticies);i++) {
		verticies[i].x += position.x;
		verticies[i].y += position.y;
		verticies[i].z += position.z;
	}
}

void Cube::setDimension(Point position)
{
	Cube::dimensions = dimensions;
	for (Point p : verticies) {
		p.x = dimensions.x;
		p.y = dimensions.y;
		p.z = dimensions.z;
	}
}

void Cube::rotateX(float angle)
{
	for (int i = 0; i <8;i++) {
		Cube::o_verticies[i] = { 
			Cube::o_verticies[i].x,
			Cube::o_verticies[i].y* std::cos(angle) - Cube::o_verticies[i].z * std::sin(angle),
			Cube::o_verticies[i].y* std::sin(angle) + Cube::o_verticies[i].z * std::cos(angle) 
		};
		}
}

void Cube::rotateY(float angle)
{
	for (int i = 0; i < 8;i++) {
		Cube::o_verticies[i] = {
			Cube::o_verticies[i].x * std::cos(angle) - Cube::o_verticies[i].z * std::sin(angle),
			Cube::o_verticies[i].y,
			Cube::o_verticies[i].x * std::sin(angle) + Cube::o_verticies[i].z * std::cos(angle)
		};
	}
}

void Cube::rotateZ(float angle)
{
	for (int i = 0; i < 8;i++) {
		Cube::o_verticies[i] = {
			Cube::o_verticies[i].y* std::cos(angle) - Cube::o_verticies[i].x * std::sin(angle),
			Cube::o_verticies[i].y * std::sin(angle) + Cube::o_verticies[i].x * std::cos(angle),
			Cube::o_verticies[i].z
		};
	}
}

void Cube::rotate(Point angle)
{
	this->rotateX(angle.x);
	this->rotateY(angle.y);
	this->rotateZ(angle.z);
}

void Cube::draw(sf::RenderWindow& window, Camera camera, Point viewdirection, unsigned int WIDTH, unsigned int HEIGHT)
{
	for (int x = 0; x < std::size(faces);x++) {
		for (int y = 0;y < std::size(faces[x]);y++) {

			struct Point a = this->o_verticies[faces[x][y]];
			struct Point b = this->o_verticies[faces[x][(y + 1) % std::size(faces[x])]];
			struct Point c = this->o_verticies[faces[x][(y + 2) % std::size(faces[x])]];
			
			a.x += camera.position.x + position.x;
			a.y += camera.position.y + position.y;
			a.z += camera.position.z + position.z;
			b.x += camera.position.x + position.x;
			b.y += camera.position.y + position.y;
			b.z += camera.position.z + position.z;
			c.x += camera.position.x + position.x;
			c.y += camera.position.y + position.y;
			c.z += camera.position.z + position.z;
			if (a.z > 0 || b.z > 0 || c.z > 0) continue;
			line(
				project(translate(a), WIDTH, HEIGHT),
				project(translate(b), WIDTH, HEIGHT),
				project(translate(c), WIDTH, HEIGHT),
				window
			);
		}
	}

}

void Cube::clean()
{
    for (int i = 0; i < 8; ++i) {
        o_verticies[i] = verticies[i];
    }
}

void Cube::line(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::RenderWindow& window)
{
	std::array line =
	{
		sf::Vertex{sf::Vector2f(p1.x, p1.y), sf::Color::Green},
		sf::Vertex{sf::Vector2f(p2.x, p2.y), sf::Color::Green},
		//sf::Vertex{sf::Vector2f(p3.x, p3.y), sf::Color::Blue},
	};
	window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

}

sf::Vector2f Cube::project(Point p, const unsigned long WIDTH, const unsigned long HEIGTH)
{
	return {
		(p.x + 1) / 2 * WIDTH,
		(1 - (p.y + 1) / 2) * HEIGTH
	};
}

Point Cube::translate(Point p)
{
	return {
		p.x / p.z,
		p.y / p.z,
		p.z
	};
}

