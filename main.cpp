#include <SFML/Graphics.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#include "Camera.h"
#include "Cube.h"

constexpr unsigned long WIDTH = 1000;
constexpr unsigned long HEIGTH = 1000;
constexpr unsigned long FPS = 60;
void input(Camera &camera, float SPEED) {

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
	Cube *cubes = static_cast<Cube*>(malloc(sizeof(Cube) * 10 * 10 * 10));
    Camera camera = Camera({ 0,0,-5 }, { 0,0,1 });
	for (int x = 0; x < 10; x++) {
        for(int y = 0; y < 10; y++) {
            for(int z = 0; z < 10; z++) {
                *(cubes + x*100 + y*10 + z) = Cube({(float)x,(float)y,-(float)z}, {0,0,0});
            }
		}
    }

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
        input(camera, 0.2);
        for (int x = 0; x < 10*10*10; x++) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::O)) {
				(*(cubes + x)).rotate({ dz, dz, dz });
            }
            (*(cubes+x)).draw(window,camera,viewdirection, WIDTH, HEIGTH);
        }
        window.display();
        for (int x = 0; x < 10*10*10; x++) {
            (*(cubes + x)).clean();
        }
    }
    cubes = nullptr;
}