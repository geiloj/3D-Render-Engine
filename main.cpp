#include <SFML/Graphics.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#include "Camera.h"
#include "Cube.h"
constexpr unsigned long WIDTH = 1000*2;
constexpr unsigned long HEIGTH = 1000*2;
constexpr unsigned long FPS = 144;
void input(Camera &camera, float SPEED) {
    SPEED = (SPEED/FPS)*60;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
    {
        camera.position.z += SPEED;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
    {
        camera.position.z -= SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        camera.position.x -= SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        camera.position.x += SPEED;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        camera.position.y += SPEED/2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
        camera.position.y -= SPEED/2;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGTH }), "3D Render Engine!");
    Camera camera = Camera({ 0,0,-5 }, { 0,0,1 });
	Cube cube = Cube({ 0,0,0 }, {0,0,0});
    window.setFramerateLimit(FPS);
    Point viewdirection = { 0,0,0, };
    float dz = 0;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        dz += 1.0 / FPS;
        window.clear();
        input(camera, 0.1);
        cube.draw(window, camera, viewdirection, WIDTH, HEIGTH);
        window.display();
		cube.clean();

    }
}