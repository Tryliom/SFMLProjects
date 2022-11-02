#include "Animation.h"

Animation::Animation(sf::Time lifeTime, const sf::Vector2f position)
{
	_lifeTime = lifeTime;
	_elapsed = sf::Time::Zero;
	_position = position;
}

bool Animation::IsAlive() const
{
	return _elapsed < _lifeTime;
}

void Animation::Update(const sf::Time elapsed)
{
	_elapsed += elapsed;
}
