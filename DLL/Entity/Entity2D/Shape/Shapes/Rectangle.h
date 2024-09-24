#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Shape/Shape.h"

SIRENITO_API class Rectangle : public Shape
{
public:

	SIRENITO_API Rectangle(glm::vec3 position, float width, float height, Color color, Renderer* renderer);
	SIRENITO_API float* GetVertices(float width, float height);
	SIRENITO_API unsigned int* GetIndices();
};