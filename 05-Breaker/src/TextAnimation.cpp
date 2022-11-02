#include "TextAnimation.h"

TextAnimation::TextAnimation(const sf::Text& text, const sf::Time lifeTime)
	: Animation(lifeTime, text.getPosition())
{
	_text = text;
}

void TextAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_text, states);
}

void TextAnimation::Update(const sf::Time elapsed)
{
	Animation::Update(elapsed);
	_text.move(0, -elapsed.asSeconds() * 50);

	// Set the alpha value of the text to the current life time
	sf::Color color = _text.getFillColor();
	color.a = 255 - static_cast<sf::Uint8>(_elapsed.asSeconds() / _lifeTime.asSeconds() * 255.0f);
	_text.setFillColor(color);

	sf::Color outlineColor = _text.getOutlineColor();
	outlineColor.a = 255 - static_cast<sf::Uint8>(_elapsed.asSeconds() / _lifeTime.asSeconds() * 255.0f);
	_text.setOutlineColor(outlineColor);
}
