#include "Cube.h"
Cube::Cube(Point position, Point dimension, unsigned int w, unsigned int h)
{
	WIDTH = w;
	HEIGHT = h;
	clean();
	Cube::dimensions = dimensions;
	for (Point p : Cube::verticies) {
		p.x = p.x + position.x;
		p.y = p.y + position.y;
		p.z = p.z + position.z;
	}
}

void Cube::setPosition(Point position)
{
	Cube::position = position;
	for (Point p : Cube::verticies) {
		p.x = position.x;
		p.y = position.y;
		p.z = position.z;
	}
}

void Cube::move(Point position)
{
	for (Point p : Cube::verticies) {
		p.x += position.x;
		p.y += position.y;
		p.z += position.z;
	}

}

void Cube::setDimension(Point position)
{
	Cube::dimensions = dimensions;
	for (Point p : Cube::verticies) {
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

void Cube::draw(sf::RenderWindow& window, Camera camera, sf::Vector2f viewdirection)
{
	for (int x = 0; x < std::size(this->faces);x++) {
		for (int y = 0;y < std::size(this->faces[x]);y++) {
			struct Point a = this->o_verticies[this->faces[x][y]];
			struct Point b = this->o_verticies[this->faces[x][(y + 1) % std::size(this->faces[x])]];
			struct Point c = this->o_verticies[this->faces[x][(y + 2) % std::size(this->faces[x])]];
			a.x += camera.position.x;
			a.y += camera.position.y;
			a.z += camera.position.z;
			b.x += camera.position.x;
			b.y += camera.position.y;
			b.z += camera.position.z;
			c.x += camera.position.x;
			c.y += camera.position.y;
			c.z += camera.position.z;
			line(
				project(translate(a), WIDTH, HEIGHT) + viewdirection,
				project(translate(b), WIDTH, HEIGHT) + viewdirection,
				project(translate(c), WIDTH, HEIGHT) + viewdirection,
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

