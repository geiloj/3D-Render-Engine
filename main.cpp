#include <SFML/Graphics.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#include "Camera.h"
#include "Cube.h"

constexpr unsigned long WIDTH = 1000;
constexpr unsigned long HEIGTH = 1000;
constexpr unsigned long FPS = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGTH }), "3D Render Engine!");
    Cube cube = Cube({ 0,0,0 }, { 0,0,0 }, WIDTH, HEIGTH);
	Camera camera = Camera({ 0,0,-5 }, { 0,0,1 });

    window.setFramerateLimit(FPS);
    Point viewdirection = { 0,0,0, };


        float yaw = 0;
        float pitch = 0;
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
                yaw += 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                yaw -= 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
                pitch -= 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
                pitch += 0.1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
			camera.position.y += 0.1;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift)) {
			camera.position.y -= 0.1;
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Q)) {
            
        }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E)) {

            }    
             viewdirection = { cos(pitch) * sin(yaw),sin(pitch),cos(pitch) * cos(yaw) };
        
        cube.rotate({dz,dz,dz});

        cube.draw(window, camera, viewdirection);
		std::cout << cube.position.z << std::endl;
        window.display();
        cube.clean();
    }
}