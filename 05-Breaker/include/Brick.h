#pragma once
#include <SFML/Graphics.hpp>

constexpr float BRICK_WIDTH = 32.0f;
constexpr float BRICK_HEIGHT = 16.0f;

class Brick final : public sf::Drawable
{
public:
	explicit Brick(const sf::Vector2f& position);

private:
	sf::RectangleShape _shape;
	bool _isDestroyed;

public:
	bool IsDestroyed() const { return _isDestroyed; }
	sf::RectangleShape GetShape() const { return _shape; }

	void Break();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
