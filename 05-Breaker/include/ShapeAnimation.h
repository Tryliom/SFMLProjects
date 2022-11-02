#pragma once
#include "Animation.h"

class ShapeAnimation final : public Animation
{
public:
	ShapeAnimation(const sf::RectangleShape& shape, sf::Time lifeTime);

private:
	sf::RectangleShape _shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Update(sf::Time elapsed) override;
};