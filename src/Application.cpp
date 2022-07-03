#include <iostream>
#include <SFML/Graphics.hpp>

// $cmake -G "MinGW Makefiles" -B build/Release -DCMAKE_BUILD_TYPE=Release
// $cmake -G "MinGW Makefiles" -B build/Debug -DCMAKE_BUILD_TYPE=Debug

int main(int argc, char **argv) {
    sf::RenderWindow window (sf::VideoMode(sf::Vector2u(800, 600), 32), "SFML works test!");
    sf::CircleShape shape (100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
