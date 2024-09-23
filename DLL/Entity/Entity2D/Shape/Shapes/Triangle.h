#pragma once
#include "Utilities/Exporter.h"
#include "Entity/Entity2D/Shape/Shape.h"

SIRENITO_API class Triangle : public Shape
{
public:

	SIRENITO_API Triangle(glm::vec3 position, float width, float height, Renderer* renderer);
	SIRENITO_API float* GetVertices(float width, float height);
	SIRENITO_API unsigned int* GetIndices();
};