#pragma once
#include "Utilities/Exporter.h"
#include "Utilities/Vector2.h"
#include "Textures/Texture.h"

SIRENITO_API class Frame
{
private:
	Vector2 minCoords;
	Vector2 maxCoords;
public:

	SIRENITO_API Frame();
	SIRENITO_API Frame(Vector2 minCoords, Vector2 maxCoords);
	SIRENITO_API Vector2 GetMin();
	SIRENITO_API Vector2 GetMax();

	SIRENITO_API bool operator ==(Frame other);
	SIRENITO_API bool operator !=(Frame other);
};