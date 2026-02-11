#pragma once
#include "Point.h"
#include "Camera.h"
//#include "VCube.h"
#include <SFML/Graphics.hpp>
#include <cmath>
class Body
{
public:
    Body();
    Body(Point position, Point dimensions);
    void setPosition(Point position);
    void move(Point position);
    void setDimension(Point position);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(Point angle);
    void draw(sf::RenderWindow& window, Camera camera, Point viewdirection, unsigned int WIDTH, unsigned int HEIGHT);
    void clean();
    Point position;
    Point dimensions;
    
#ifndef inherit
	struct Point vertices[1];
    struct Point o_verticies[1];
    int faces[1][1];
#endif
    Body(const Body& other);
    Body& operator=(const Body& other);
private:
    void line(sf::Vector2f p1, sf::Vector2f p2, sf::RenderWindow& window);
    sf::Vector2f project(Point p, const unsigned long WIDTH, const unsigned long HEIGTH);
    Point translate(Point p);

};
// Implementierung des Copy-Konstruktors und Copy-Assignment-Operators für Cube

