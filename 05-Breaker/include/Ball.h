#pragma once
#include "Player.h"
#include "Spark.h"
#include "SFML/Graphics.hpp"

const sf::Time SPARK_COOLDOWN = sf::seconds(0.01f);

class Ball final : public sf::Drawable
{
public:
	Ball();

private:
	sf::CircleShape _shape;
	sf::Texture _texture;
	sf::Vector2f _velocity;
	std::vector<Spark> _sparks;

	sf::Time _sparkCooldown;

	float getLeftSide() const { return _shape.getPosition().x - _shape.getRadius(); }
	float getRightSide() const { return _shape.getPosition().x + _shape.getRadius(); }
	float getTopSide() const { return _shape.getPosition().y - _shape.getRadius(); }
	float getBottomSide() const { return _shape.getPosition().y + _shape.getRadius(); }

	void moveOutOfBounds(const sf::Shape& bounds);

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
