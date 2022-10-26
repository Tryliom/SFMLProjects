#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"

class Ball final : public sf::Drawable
{
public:
	Ball();

private:
	sf::CircleShape _shape;
	sf::Vector2f _velocity;

public:
	void SetPosition(const sf::Vector2f& position) { _shape.setPosition(position); }
	sf::Vector2f GetPosition() const { return _shape.getPosition(); }
	float GetRadius() const { return _shape.getRadius(); }
	bool IsMoving() const { return _velocity.x != 0.0f || _velocity.y != 0.0f; }

	void Update(sf::Time elapsed);
	bool IsColliding(const sf::Shape& bounds) const;
	void Bounce(const sf::Shape& bounds);
	void Bounce(const Bar& bar);
	void Launch(const sf::Vector2f& direction);
	void Reset();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
