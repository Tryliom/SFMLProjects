#pragma once
#include "Bar.h"

class Player final : public sf::Drawable
{
public:
	explicit Player(const sf::Vector2f& position);

private:
	std::vector<Bar> _bars;

public:
	[[nodiscard]] std::vector<Bar> GetBars() const { return _bars; }
	[[nodiscard]] sf::Vector2f GetBallPosition() const;
	[[nodiscard]] float GetVelocity() const { return _bars[0].GetVelocity(); }
	[[nodiscard]] bool IsColliding(const sf::Shape& bounds);

	void MoveLeft(const sf::Time elapsed);
	void MoveRight(const sf::Time elapsed);
	void ResetDirection();
	void SetPosition(const int x);
	void Stop(sf::RectangleShape wall);

	void Update(const sf::Time elapsed);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};