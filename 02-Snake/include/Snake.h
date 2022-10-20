#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

constexpr int RADIUS = 5;
constexpr int SPEED = RADIUS * 2;
constexpr int START_SIZE = 3;
constexpr float START_X = 400.0f;
constexpr float START_Y = 300.0f;
const sf::Time UPDATE_PER_SECOND = sf::seconds(1.0f / 30.0f);

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake final : public sf::Drawable
{
public:
	Snake(bool useIA = false);

private:
	std::vector<sf::CircleShape> _body;
	Direction _direction;
	bool _useIA;

	bool _canTakeDamage;
	bool _canChangeDirection;

	sf::Time _elapsed;
	sf::Time _invincibilityTime;

	[[nodiscard]] sf::Vector2f getNextPosition(Direction nextDirection) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateIA(sf::Vector2f eggPosition);

public:
	void ChangeDirection(const Direction direction);
	void Update(sf::Time elapsed, sf::Vector2f eggPosition);
	void Grow();
	void TakeDamage();

	[[nodiscard]] bool CanEatEgg(const sf::Vector2f& eggPosition) const;
	[[nodiscard]] Direction GetDirection() const { return _direction; }
	[[nodiscard]] std::vector<sf::Vector2f> GetPositions() const;
	[[nodiscard]] bool IsAlive() const { return static_cast<int>(_body.size()) > 0; }
	[[nodiscard]] bool Hit(const std::vector<sf::Vector2f>& opponentPositions) const;
};