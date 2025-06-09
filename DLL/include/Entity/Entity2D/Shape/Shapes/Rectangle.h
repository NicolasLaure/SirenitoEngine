#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Shape/Shape.h"

SIRENITO_API class Rectangle : public Shape
{
public:

	SIRENITO_API Rectangle(Vector3 position, float width, float height, Color material, Renderer* renderer);
	SIRENITO_API ~Rectangle();
	SIRENITO_API float* GetVertices(float width, float height);
	SIRENITO_API unsigned int* GetIndices();
};