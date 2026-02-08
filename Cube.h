#pragma once
#include "Point.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <cmath>
class Cube
{
public:
    Cube(Point position, Point dimensions, unsigned int w, unsigned int h);
    void setPosition(Point position);
    void move(Point position);
    void setDimension(Point position);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void rotate(Point angle);
    void draw(sf::RenderWindow& window, Camera camera, Point viewdirection);
    void clean();
    Point position;
    Point dimensions;

    struct Point o_verticies[8];
    struct Point verticies[8] = {
    {0.5,0.5,0.5},
    {-0.5,0.5,0.5},
    {-0.5,-0.5,0.5},
    {0.5,-0.5,0.5},
    {0.5,0.5,-0.5},
    {-0.5,0.5,-0.5},
    {-0.5,-0.5,-0.5},
    {0.5,-0.5,-0.5}
    };
    const int faces[8][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {0,4,4,0},
        {1,5,5,1},
        {2,6,6,2},
        {3,7,7,3},
    };
private:
    unsigned int WIDTH;
    unsigned int HEIGHT;
    void line(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::RenderWindow& window);
    sf::Vector2f project(Point p, const unsigned long WIDTH, const unsigned long HEIGTH);
    Point translate(Point p);

};