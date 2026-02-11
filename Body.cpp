#include "Body.h"
Body::Body()
{
}
Body::Body(Point position, Point dimension)
{
	clean();
	Body::position = position;
	Body::dimensions = dimensions;
	for (int i = 0;i < std::size(vertices);i++) {
		o_verticies[i].x = vertices[i].x + position.x;
		o_verticies[i].y = vertices[i].y + position.y;
		o_verticies[i].z = vertices[i].z + position.z;
	}
}
Body::Body(const Body& other)
	: position(other.position),
	dimensions(other.dimensions){
	for (int i = 0; i < 8; ++i) {
		o_verticies[i] = other.o_verticies[i];
	}
}

Body& Body::operator=(const Body& other)
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

void Body::setPosition(Point position)
{
	Body::position = position;
	for (int i = 0;i < std::size(vertices);i++) {
		vertices[i].x = position.x;
		vertices[i].y = position.y;
		vertices[i].z = position.z;
	}
}

void Body::move(Point position)
{
	for (int i = 0;i < std::size(vertices);i++) {
		vertices[i].x += position.x;
		vertices[i].y += position.y;
		vertices[i].z += position.z;
	}
}

void Body::setDimension(Point position)
{
	Body::dimensions = dimensions;
	for (Point p : vertices) {
		p.x = dimensions.x;
		p.y = dimensions.y;
		p.z = dimensions.z;
	}
}

void Body::rotateX(float angle)
{
	for (int i = 0; i < std::size(vertices);i++) {
		Body::o_verticies[i] = { 
			Body::o_verticies[i].x,
			Body::o_verticies[i].y * std::cos(angle) - Body::o_verticies[i].z * std::sin(angle),
			Body::o_verticies[i].y * std::sin(angle) + Body::o_verticies[i].z * std::cos(angle)
		};
		}
}

void Body::rotateY(float angle)
{
	for (int i = 0; i < std::size(vertices);i++) {
		Body::o_verticies[i] = {
			vertices[i].x * std::cos(angle) - vertices[i].z * std::sin(angle),
			vertices[i].y,
			vertices[i].x * std::sin(angle) + vertices[i].z * std::cos(angle)
		};
	}
}

void Body::rotateZ(float angle)
{
	for (int i = 0; i < std::size(vertices);i++) {
		Body::o_verticies[i] = {
			Body::o_verticies[i].y * std::cos(angle) - Body::o_verticies[i].x * std::sin(angle),
			Body::o_verticies[i].y * std::sin(angle) + Body::o_verticies[i].x * std::cos(angle),
			Body::o_verticies[i].z
		};
	}
}

void Body::rotate(Point angle)
{
	this->rotateX(angle.x);
	this->rotateY(angle.y);
	this->rotateZ(angle.z);
}

void Body::draw(sf::RenderWindow& window, Camera camera, Point viewdirection, unsigned int WIDTH, unsigned int HEIGHT)
{
	for (int x = 0; x < std::size(faces);x++) {
		for (int y = 0;y < std::size(faces[x]);y++) {

			struct Point a = this->o_verticies[faces[x][y]];
			struct Point b = this->o_verticies[faces[x][(y + 1) % std::size(faces[x])]];
			
			a.x += camera.position.x + position.x;
			a.y -= camera.position.y + position.y;
			a.z += camera.position.z + position.z;
			b.x += camera.position.x + position.x;
			b.y -= camera.position.y + position.y;
			b.z += camera.position.z + position.z;
			if (a.z > 0 || b.z > 0) continue;
			line(
				project(translate(a), WIDTH, HEIGHT),
				project(translate(b), WIDTH, HEIGHT),
				window
			);
		}
	}

}

void Body::clean()
{
    for (int i = 0; i < 8; ++i) {
        o_verticies[i] = vertices[i];
    }
}

void Body::line(sf::Vector2f p1, sf::Vector2f p2, sf::RenderWindow& window)
{
	std::array line =
	{
		sf::Vertex{sf::Vector2f(p1.x, p1.y), sf::Color::Green},
		sf::Vertex{sf::Vector2f(p2.x, p2.y), sf::Color::Green},
		//sf::Vertex{sf::Vector2f(p3.x, p3.y), sf::Color::Blue},
	};
	window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

}

sf::Vector2f Body::project(Point p, const unsigned long WIDTH, const unsigned long HEIGTH)
{
	return {
		(p.x + 1) / 2 * WIDTH,
		(1 - (p.y + 1) / 2) * HEIGTH
	};
}

Point Body::translate(Point p)
{
	return {
		p.x / p.z,
		-(p.y / p.z),
		p.z
	};
}

