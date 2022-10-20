#include "PaintingFactory.h"

sf::Drawable* PaintingFactory::GetPainting(const PaintingType type, sf::Vector2u windowSize)
{
	if (type == PaintingType::FIRST)
	{
		return new FirstPainting(windowSize);
	}
	
	return nullptr;
}
