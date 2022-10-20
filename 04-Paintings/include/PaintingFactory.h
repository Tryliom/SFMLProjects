#pragma once
#include "FirstPainting.h"

enum class PaintingType
{
	FIRST, SECOND, THIRD, END
};

namespace PaintingFactory
{
	sf::Drawable* GetPainting(PaintingType type, sf::Vector2u windowSize);
}