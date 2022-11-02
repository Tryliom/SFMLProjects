#pragma once
#include "Animation.h"

class TextAnimation final : public Animation
{
public:
	TextAnimation(const sf::Text& text, sf::Time lifeTime);

private:
	sf::Text _text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void Update(sf::Time elapsed) override;

};