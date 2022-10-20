#include "PaintingFactory.h"

#include "SecondPainting.h"

sf::Drawable* PaintingFactory::GetPainting(const PaintingType type, sf::Vector2u windowSize)
{
	if (type == PaintingType::FIRST)
	{
		return new FirstPainting(windowSize);
	}

	if (type == PaintingType::SECOND)
	{
		return new SecondPainting(windowSize);
	}
	
	return nullptr;
}
