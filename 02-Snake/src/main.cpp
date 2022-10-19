#include <random>

#include "SFML/Graphics.hpp"

int GetInt(const int min, const int max)
{
    std::random_device osSeed;
    const uint_least32_t seed = osSeed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<uint_least32_t> distribute(min, max);

    return static_cast<int>(distribute(generator));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Game");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    // Set shape position to center of window
    shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // Basic Setup of the window
    // Vertical sync, framerate
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    while (window.isOpen())
    {

        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    shape.move(-10, 0);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    shape.move(10, 0);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    shape.move(0, -10);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    shape.move(0, 10);
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    shape.setPosition(event.mouseMove.x - shape.getRadius(), event.mouseMove.y - shape.getRadius());
                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    shape.setRadius(shape.getRadius() + 1);
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    shape.setRadius(shape.getRadius() - 1);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // Change the color of the shape by a random one
                    shape.setFillColor(sf::Color(GetInt(0, 255), GetInt(0, 255), GetInt(0, 255)));
                }
            }
        }

        // Graphical Region
        window.clear(sf::Color::Black);

        // Draw stuff
        window.draw(shape);

        // Window Display
        window.display();

    }
}
