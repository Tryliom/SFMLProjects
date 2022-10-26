#pragma once
#include "SFML/Graphics.hpp"

constexpr float SPEED = 300.0f;
constexpr float MAX_SPEED = 600.0f;

class Bar final : public sf::Drawable
{
public:
	explicit Bar(sf::Vector2f position);

private:
	sf::Texture _texture;
	sf::RectangleShape _shape;
	float _velocity;
	bool _isMoving;

public:
	sf::RectangleShape GetBar() const { return _shape; }
	float GetVelocity() const { return _velocity; }
	sf::Vector2f GetTopMiddlePosition() const;
	void ResetDirection() { _isMoving = false; }

	void MoveLeft(const sf::Time elapsed);
	void MoveRight(const sf::Time elapsed);

	void Update(const sf::Time elapsed);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};