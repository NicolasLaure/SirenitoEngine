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

	SIRENITO_API Frame();
	SIRENITO_API Frame(Vector2f minCoords, Vector2f maxCoords);
	SIRENITO_API Vector2f GetMin();
	SIRENITO_API Vector2f GetMax();

	SIRENITO_API bool operator ==(Frame other);
	SIRENITO_API bool operator !=(Frame other);
};