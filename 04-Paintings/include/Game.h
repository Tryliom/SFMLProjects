#pragma once
#include <SFML/Graphics.hpp>

#include "PaintingFactory.h"

class Game
{
public:
	Game();

private:
	sf::RenderWindow _window;
	sf::Drawable* _drawable;

	PaintingType _paintingType = PaintingType::FIRST;

public:
	void Start();
};
