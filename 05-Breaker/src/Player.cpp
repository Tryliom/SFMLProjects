#include "Player.h"

Player::Player(const sf::Vector2f& position)
{
	_bars.emplace_back(position);
}

sf::Vector2f Player::GetBallPosition() const
{
	return _bars[0].GetTopMiddlePosition();
}

bool Player::IsColliding(const sf::Shape& bounds) const
{
	for (const auto& bar : _bars)
	{
		if (bar.GetBar().getGlobalBounds().intersects(bounds.getGlobalBounds()))
		{
			return true;
		}
	}

	return false;
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

void Player::ResetDirection()
{
	for (auto& bar : _bars)
	{
		bar.ResetDirection();
	}
}

void Player::Stop(sf::RectangleShape wall)
{
	for (auto& bar : _bars)
	{
		bar.Stop(wall);
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
