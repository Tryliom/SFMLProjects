#include "Player.h"

Player::Player(const sf::Vector2f& position)
{
	_bars.emplace_back(position);
}

sf::Vector2f Player::GetBallPosition() const
{
	return _bars[0].GetTopMiddlePosition();
}

void Player::MoveLeft(const sf::Time elapsed)
{
	for (auto& bar : _bars)
	{
		bar.MoveLeft(elapsed);
	}
}

void Player::MoveRight(const sf::Time elapsed)
{
	for (auto& bar : _bars)
	{
		bar.MoveRight(elapsed);
	}
}

void Player::Update(const sf::Time elapsed)
{
	for (auto& bar : _bars)
	{
		bar.Update(elapsed);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& bar : _bars)
	{
		target.draw(bar, states);
	}
}
