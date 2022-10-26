#include "GameController.h"

int main()
{
	sf::RenderWindow window{ sf::VideoMode{ 800, 600 }, "Breaker" };
	GameController gameController(window);
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event{};

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			gameController.CheckInput(event);
		}
		
		gameController.Update(clock.restart());

		window.clear();

		gameController.Draw(window);

		window.display();
	}
}
