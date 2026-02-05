#include <SFML/Graphics.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#include "Camera.h"
#include "Cube.h"
#define WIDTH 800
#define HEIGTH 800
#define FPS 60

int main()
{
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGTH }), "3D Render Engine!");
    Cube cube = Cube({ 0,0,0 }, { 0,0,0 }, WIDTH, HEIGTH);
    Cube cube2 = Cube({ 0,0,0 }, { 0,0,0 }, WIDTH, HEIGTH);
	Camera camera = Camera({ 0,0,-5 }, { 0,0,1 });

    window.setFramerateLimit(FPS);
        sf::Vector2f viewdirection = sf::Vector2f(0,0);


        float angle = 0;
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

              
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
        {
			camera.position.z += 0.02;
        } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
        {
			camera.position.z -= 0.02;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
			camera.position.x -= 0.02;
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
			camera.position.x += 0.02;
		}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
            viewdirection.x += 4;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            viewdirection.x -= 4;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            viewdirection.y -= 4;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            viewdirection.y += 4;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
			camera.position.y += 0.1;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
			camera.position.y -= 0.1;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
            cube.move({0,0.1,0});
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {
            cube.move({ 0,-0.1,0 });
        }    
        cube.rotateY(-dz);
        cube.rotateX(dz);
        cube.rotateZ(-dz);
        cube.draw(window, camera, viewdirection);
        cube2.draw(window, camera, viewdirection);
        window.display();
        cube.clean();
        cube2.clean();
    }
}