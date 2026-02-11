#pragma once
#include "Point.h"
#include "Camera.h"
#include "VCube.h"
#include <SFML/Graphics.hpp>
#include <cmath>
class Cube
{
public:
    Cube();
    Cube(Point position, Point dimensions);
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

    struct Point o_verticies[8];

    Cube(const Cube& other);
    Cube& operator=(const Cube& other);
private:
    void line(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::RenderWindow& window);
    sf::Vector2f project(Point p, const unsigned long WIDTH, const unsigned long HEIGTH);
    Point translate(Point p);

};
// Implementierung des Copy-Konstruktors und Copy-Assignment-Operators für Cube

