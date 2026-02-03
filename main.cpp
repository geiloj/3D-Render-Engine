#include <SFML/Graphics.hpp>
#include <cmath>
#include <corecrt_math_defines.h>
#include <iostream>
#define WIDTH 800
#define HEIGTH 800
#define FPS 60

struct Point {
    float x;
    float y;
    float z;
};

sf::Vector2f project(Point p){
    return {
        (p.x + 1) / 2 * WIDTH,
        (1-(p.y + 1) / 2) * HEIGTH
    };
}

Point translate(Point p){
    return {
        p.x / p.z,
        p.y / p.z,
        p.z
    };
}
Point updateZ(Point p, float dz) {
    return {p.x,p.y,p.z + dz};
}
Point rotate_xz(Point p, float angle) {
    return {
        p.x * std::cos(angle) - p.z * std::sin(angle),
        p.y,
        p.x * std::sin(angle) + p.z * std::cos(angle)
    };

}
void line(sf::Vector2f p1, sf::Vector2f p2, sf::RenderWindow& window) {
    std::array line =
    {
        sf::Vertex{sf::Vector2f(p1.x, p1.y), sf::Color::Green},
        sf::Vertex{sf::Vector2f(p2.x, p2.y), sf::Color::Green}
    };
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}
int main()
{
    sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGTH }), "SFML works!");




    struct Point Cube[] = {
        {0.5,0.5,0.5},
        {-0.5,0.5,0.5},
        {-0.5,-0.5,0.5},
        {0.5,-0.5,0.5},
        {0.5,0.5,-0.5},
        {-0.5,0.5,-0.5},
        {-0.5,-0.5,-0.5},
        {0.5,-0.5,-0.5}
    };
    const int faces[6][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {0,4,4,0},
        {1,5,5,1},
        {2,6,6,2},
        {3,7,7,3}
    };
    window.setFramerateLimit(FPS);


        float angle = 0;
        float dz = 0;
        float distance = 2;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        dz += 1.0 / FPS;
        angle += 2*M_PI;
        window.clear();

        for (int x = 0; x < std::size(faces);x++) {
            for (int y = 0;y < std::size(faces[x]);y++) {
                const struct Point a = Cube[faces[x][y]];
                const struct Point b = Cube[faces[x][(y+1)%std::size(faces[x])]];
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
                {
                    distance -= 0.001;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
                {
                    distance += 0.001;
                }
                line(
                    project(translate(updateZ(rotate_xz(a, dz), distance))),
                    project(translate(updateZ(rotate_xz(b, dz), distance))),
                    window
                    );
            }
        }

        window.display();
    }
}