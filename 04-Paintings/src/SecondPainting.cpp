#include "SecondPainting.h"

#include "Random.h"

SecondPainting::SecondPainting(sf::Vector2u windowSize)
{
	// Draw squares with random red colors with the style of Vera Molnar
	const auto width = static_cast<float>(windowSize.x);
	const auto height = static_cast<float>(windowSize.y);
	auto squareSize = 20.0f;

	for (auto x = 0.0f; x < width; x += squareSize)
	{
		for (auto y = 0.0f; y < height; y += squareSize)
		{
			sf::RectangleShape shape;

			shape.setPosition(x, y);
			shape.setSize({ squareSize, squareSize });
			shape.setFillColor(getRandomRedColor());
			shape.setOutlineColor(sf::Color::Black);
			shape.setOutlineThickness(2.0f);

			_shapes.push_back(shape);
		}
	}
}

sf::Color SecondPainting::getRandomRedColor()
{
	// Get random red color tainted with a bit of green and blue
	const float hue = Random::GetFloat(320, 358);
	const float saturation = Random::GetFloat(30, 70);
	const float value = Random::GetFloat(80, 90);

	return hsvToRgb(hue, saturation, value);
}

sf::Color SecondPainting::hsvToRgb(float H, float S, float V)
{
	// Convert HSV to RGB
	float s = S / 100;
	float v = V / 100;
	float C = s * v;
	float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (H >= 0 && H < 60) {
		r = C, g = X, b = 0;
	}
	else if (H >= 60 && H < 120) {
		r = X, g = C, b = 0;
	}
	else if (H >= 120 && H < 180) {
		r = 0, g = C, b = X;
	}
	else if (H >= 180 && H < 240) {
		r = 0, g = X, b = C;
	}
	else if (H >= 240 && H < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}
	int R = (r + m) * 255;
	int G = (g + m) * 255;
	int B = (b + m) * 255;

	return { static_cast<sf::Uint8>(R), static_cast<sf::Uint8>(G), static_cast<sf::Uint8>(B) };
}

void SecondPainting::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	for (const auto& shape : _shapes)
	{
		target.draw(shape, states);
	}
}
