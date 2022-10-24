#define SFML_DEFINE_DEDICATED_GPU_PREFERENCE
#include <iostream>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
int main()
{
    sf::RenderWindow window;
    sf::CircleShape c1(50.0f,300);
    c1.setFillColor(sf::Color::White);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(800, 600, desktop.bitsPerPixel), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event));
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(c1);
        window.display();
    }
	return 0;
}