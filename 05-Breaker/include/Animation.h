#pragma once
#include <SFML/Graphics.hpp>

class Animation : public sf::Drawable
{
public:
	Animation(sf::Time lifeTime, sf::Vector2f position);

protected:
	sf::Time _elapsed;
	sf::Time _lifeTime;
	sf::Vector2f _position;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
public:
	[[nodiscard]] bool IsAlive() const;
	virtual void Update(sf::Time elapsed);
};
