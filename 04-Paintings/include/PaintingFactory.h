#pragma once
#include "FirstPainting.h"

enum class PaintingType
{
	FIRST, SECOND, END
};

namespace PaintingFactory
{
	sf::Drawable* GetPainting(PaintingType type, sf::Vector2u windowSize);
}