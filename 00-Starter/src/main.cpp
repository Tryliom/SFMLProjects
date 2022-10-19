#include "SFML/Graphics.hpp"

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
		}

        // Graphical Region
        window.clear(sf::Color::Black);

		// Draw stuff
        window.draw(shape);

        // Window Display
        window.display();

    }
}
