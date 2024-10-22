#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/Vector2.h"
#include "Textures/Texture.h"

SIRENITO_API class Frame
{
private:
	Vector2f minCoords;
	Vector2f maxCoords;
public:

	Frame(Vector2f minCoords, Vector2f maxCoords);
};