#include "FirstPainting.h"

#include <utility>
#include "Random.h"

FirstPainting::FirstPainting(sf::Vector2u windowSize)
{
	// Draw random squares with the style of Vera Molnar
	auto width = static_cast<float>(windowSize.x);
	auto height = static_cast<float>(windowSize.y);

	sf::RectangleShape firstShape;
	float side = Random::GetFloat(width / 7, width / 2) - width / 8;
	firstShape.setSize(sf::Vector2f(side, side));

	addShape(firstShape, windowSize);

	sf::RectangleShape lastShape = firstShape;

	for (float i = 1.0f; i < 5.0f; i += 1.0f)
	{
		sf::RectangleShape shape = lastShape;
		side = Random::GetFloat(
			width / (7.0f - i), 
			width / 2.0f
		) - width / (7.0f - i + 1.0f);
		shape.setSize(sf::Vector2f(side, side));

		addShape(shape, windowSize);

		lastShape = shape;
	}
}

void FirstPainting::addShape(sf::RectangleShape& shape, sf::Vector2u windowSize)
{
	auto width = static_cast<float>(windowSize.x);
	auto height = static_cast<float>(windowSize.y);
	sf::RectangleShape first = shape;

	first.setOrigin(first.getSize() / 2.0f);
	first.setPosition(sf::Vector2f(
		Random::GetFloat(width / 2.0f - first.getSize().x / 2.0f, width / 2.0f + first.getSize().x / 2.0f),
		Random::GetFloat(height / 2.0f - first.getSize().y / 2.0f, height / 2.0f + first.getSize().y / 2.0f)
	));
	first.setOutlineThickness(3);
	first.setFillColor(sf::Color::Transparent);

	sf::RectangleShape second = first;
	
	first.setOutlineColor(sf::Color::Black);
	second.setOutlineColor(sf::Color(0, 0, 0, 100));
	second.move(30, 20);

	_shapes.emplace_back(first, second);
}

void FirstPainting::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& shape : _shapes)
	{
		target.draw(shape.second, states);
		target.draw(shape.first, states);
	}
}
